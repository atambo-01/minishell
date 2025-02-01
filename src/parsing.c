/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:39 by atambo            #+#    #+#             */
/*   Updated: 2025/02/01 13:37:00 by atambo           ###   ########.fr       */
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
//	c->k += 1;
}

void	ft_handle_space_or_end(char*line, t_list **token, t_count *c)
{
	c->end = (line[c->k + 1] == 0);
	c->temp = c->k + c->end - c->last + 1;
	printf("c->temp=%d\nc->last=%d\n", c->temp, c->last);
	add_token(line, token, c);
	skip_spaces(line, c);
	c->last = c->k;
}

void	ft_get_token_if(char*line, t_list **token, t_count *c)
{
	if (c->q == 0 && line[c->k] == '|')
	{
		ft_handle_pipe(line, token, c);
	}
	else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
	{
		printf("handle_space_end c->k=%d\n", c->k);
		ft_handle_space_or_end(line, token, c);
	}
}

t_list	*ft_get_token(char *line)
{
	t_count	c;
	t_list	*token;
	char	*trim;

	if (!(trim = ft_strtrim(line, " ")))
		return(NULL);
	token = NULL;
	ft_counter(&c);
	while (trim[c.k])
	{
		ft_get_token_if(trim, &token, &c);
		ft_process_quotes(trim[c.k], &c);
		if(trim[c.k + 1] == 0 && trim[c.k] != ' ' && trim[c.k - 1] == ' ')
		{
			c = (t_count){0, 0, c.k, c.k, c.q, 2, 0};
			add_token(trim, &token, &c);
			break;
		}
		else
			(c.k)++;
	}
	ft_token_ls(token);
	if (c.q != 0)
		printf("error:unclosed quotes\n");
	ft_free_p((void **)&(trim));
	return (token);
}
