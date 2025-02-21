/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:39 by atambo            #+#    #+#             */
/*   Updated: 2025/02/21 03:32:25 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_process_quotes(char ch, t_count *c)
{
	if (ch == '"' && c->q == 0)
		c->q = 1;
	else if (ch == '"' && c->q == 1)
		c->q = 0;
	if (ch == '\'' && c->q == 0)
		c->q = 2;
	else if (ch == '\'' && c->q == 2)
		c->q = 0;
}

void	ft_handle_pipe(char*line, t_list **token, t_count *c)
{
	if (c->k >= 1 && line[c->k - 1] != ' ')
	{
		c->temp = c->k - c->last + 1;
		add_token(line, token, c);
	}
	add_pipe(token);
	skip_spaces(line, c);
	c->last = c->k + 1;
}

void	ft_handle_ctrl_op(char *line, t_list **token, t_count *c, int cop)
{
	if (c->k >= 1 && line[c->k - 1] != ' ')
	{
		c->temp = c->k - c->last + 1;
		add_token(line, token, c);
	}
	add_ctrl_op(token, cop);
	skip_spaces(line, c);
	if (cop >= 4)
		c->k += 1;
	skip_spaces(line, c);
	c->last = c->k + 1;
}


void	ft_handle_space_or_end(char*line, t_list **token, t_count *c)
{	
	c->end = 0;
	if (line[c->k + 1] == 0)
		c->end = 1;
	c->temp = c->k + c->end - c->last + 1;
	add_token(line, token, c);
	skip_spaces(line, c);
	c->last = c->k + 1;
}

void	ft_get_token_if(char *line, t_list **token, t_count *c)
{
	int	cop;

	cop = ft_cop(&line[c->k]);
	ft_process_quotes(line[c->k], c);
	if ( c->q == 0 && cop != 0)
	{
		ft_handle_ctrl_op(line, token, c, cop);
	}
	else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
	{
		ft_handle_space_or_end(line, token, c);
	}
}

char *pre_ft_get_token(char *line, t_env *env, const int prev_exit)
{
    char *trim;
    char *exp;

    if (ft_check_quotes(line) != 0) 
        return (NULL);
	if (ft_cop_syntax(line) != 0)
		return (NULL);
	if (!(trim = ft_strtrim(line, " ")))
		return (NULL);
    exp = ft_expand(trim, env, prev_exit);
    free(trim);
    return (exp);
}

t_list *ft_token(char *line, t_env *env, const int prev_exit)
{
    t_count c;
    t_list  *token;
    char    *exp;

    if (!(exp = pre_ft_get_token(line, env, prev_exit)))
        return (NULL);

    token = NULL;
    ft_counter(&c);
    while (exp[c.k])
    {
		ft_get_token_if(exp, &token, &c);
        (c.k)++;
    }
    free(exp);
    return (token);
}
