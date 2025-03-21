/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:13:24 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:17:34 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handle_ctrl_op(char *line, t_token **token, t_count *c, int cop)
{
	if (c->k > 0 && line[c->k - 1] != ' ')
	{
		c->temp = c->k - c->last + 1;
		ft_add_token(line, token, c);
	}
	ft_add_ctrl_op(token, cop);
	ft_skip_spaces(line, c);
	if (cop >= 4)
		c->k += 1;
	ft_skip_spaces(line, c);
	c->last = c->k + 1;
}

void	ft_handle_space_or_end(char*line, t_token **token, t_count *c)
{
	c->end = 0;
	if (line[c->k + 1] == 0)
		c->end = 1;
	c->temp = c->k + c->end - c->last + 1;
	ft_add_token(line, token, c);
	ft_skip_spaces(line, c);
	c->last = c->k + 1;
}

void	ft_get_token_if(char *line, t_token **token, t_count *c)
{
	int	cop;

	cop = ft_cop(&line[c->k]);
	ft_process_quotes(line[c->k], c);
	if (c->q == 0 && cop != 0)
	{
		ft_handle_ctrl_op(line, token, c, cop);
	}
	else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
	{
		ft_handle_space_or_end(line, token, c);
	}
}

char	*ft_pre_get_token(char *line, t_env *env, int exit, t_main_vars *mv)
{
	char	*exp;
	char	*trim;
	int		status;

	status = 0;
	status = ft_check_quotes(line);
	if (status == 0)
	{
		status = ft_cop_syntax(line);
		if (status == 0)
		{
			exp = ft_expand(line, env, exit, 0);
			trim = ft_strtrim(exp, " \t");
			free(exp);
			return (trim);
		}
	}
	mv->exit = status;
	return (NULL);
}

t_token	*ft_token(char *line, t_env *env, int prev_exit, t_main_vars *mv)
{
	t_count		c;
	char		*exp;
	t_token		*token;

	exp = ft_pre_get_token(line, env, prev_exit, mv);
	if (!exp)
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
