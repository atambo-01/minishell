/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:06:53 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_skip_spaces(char *line, t_count *c)
{
	if (!line || !c)
		return ;
	if (line[c->k + 1] != 0)
	{
		while (line[c->k + 1] == ' ' || line[c->k + 1] == '\t')
			(c->k)++;
	}
}

t_token	*ft_get_tail(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	ft_add_token(char *line, t_token **p_token, t_count *c)
{
	t_token	*token;
	t_token	*curr;

	token = NULL;
	if (!line || !c)
		return ;
	token = ft_malloc(sizeof(t_token));
	token->s = ft_malloc(sizeof(char *) * (c->temp + 1));
	ft_strlcpy(token->s, &line[c->last], c->temp);
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		curr = ft_get_tail(*p_token);
		curr->next = token;
	}
}

void	ft_add_pipe(t_token **p_token)
{
	t_token	*curr;
	t_token	*token;

	if (!p_token || !*p_token)
		return ;
	token = ft_malloc(sizeof(t_token));
	token->s = ft_strdup("|");
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		curr = ft_get_tail(*p_token);
		curr->next = token;
	}
}

void	ft_add_ctrl_op(t_token **p_token, int cop)
{
	t_token	*curr;
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	if (cop == 1)
		token->s = ft_strdup("|");
	else if (cop == 2)
		token->s = ft_strdup(">");
	else if (cop == 3)
		token->s = ft_strdup("<");
	else if (cop == 4)
		token->s = ft_strdup(">>");
	else if (cop == 5)
		token->s = ft_strdup("<<");
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		curr = ft_get_tail(*p_token);
		curr->next = token;
	}
}
