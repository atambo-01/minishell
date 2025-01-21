/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/01/21 19:16:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_count	*ft_counter(void)
{
	t_count	*c;

	c = ft_malloc(sizeof(t_count));
	if (!c)
		return(NULL);
	c->i = 0;
	c->j = 0;
	c->k = 0;
	c->last = 0;
	c->q = 0;
	c->temp = 0;
	c->end = 0;
	/*
	free(c);
	c = NULL;
	 */
	return (c);
}


void	*add_token(char *line, t_list **p_token, t_count **p_c)
{
	t_list	*token;
	t_count	*c;
	char	*process;
	
	token = NULL;
	if (!line || !p_c)
		return(NULL);
	c = *p_c;
	token = ft_malloc(sizeof(t_list));
	token->s = ft_malloc(sizeof(char *) * (c->temp + 1));
	ft_strlcpy(token->s, &line[c->last], c->temp + 1);
	process = ft_get_token_2(token->s, c);
	token->s = process;
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		while(*p_token->next)
			(*p_token) = (*p_token)->next;
		(*p_token)->next = token;
	}
	return (token);
}

void	*add_pipe(t_list **p_token)
{
	t_list	*token;

	token->s = ft_strdup("|");
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		while(*p_token->next)
			*p_token = (*p_token)->next;
		*p_token->next = token;
	}
}

void	skip_spaces(char *line, t_count **p_c)
{
	t_count	*c;
	
	if (!line || !p_c || !*p_c)
		return;
	c = *p_c;
	while (line[c->k] == ' ')
		(c->k)++;
}
