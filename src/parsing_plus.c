/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/02/27 17:20:32 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_skip_spaces(char *line, t_count *c)
{
	if (!line || !c)
		return ;
	if (line[c->k + 1] != 0)
	{
		while (line[c->k + 1] == ' ')
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

void	ft_counter(t_count *c)
{
	if (!c)
		return ;
	(c)->i = 0;
	(c)->j = 0;
	(c)->k = 0;
	(c)->last = 0;
	(c)->q = 0;
	(c)->temp = 0;
	(c)->end = 0;
}

void	ft_add_token(char *line, t_token **p_token, t_count *c)
{
	char	*process;
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

	if (!p_token || !*p_token)
		return ;
	token = ft_malloc(sizeof(t_token));
	if (cop == 1)
		token->s = ft_strdup("|");
	else if (cop == 2)
		token->s = ft_strdup(">");
	else if (cop == 3 ) 
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

