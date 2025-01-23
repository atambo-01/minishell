/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/01/23 17:16:29 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*ft_get_tail(t_list *node)
{
	if (!node)
		return(NULL);
	while(node->next)
		node = node->next;
	return(node);
}

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


void	add_token(char *line, t_list **p_token, t_count **p_c)
{
	t_count	*c;
	t_list	*token;
	char	*process;
	t_list	*curr;
	
	token = NULL;
	if (!line || !p_c)
		return ;
	c = *p_c;
	token = ft_malloc(sizeof(t_list));
	token->s = ft_malloc(sizeof(char *) * (c->temp + 1));
	ft_strlcpy(token->s, &line[c->last], c->temp); //it was + 1 before, removing it worked but why ??
	process = ft_get_token_2(token->s, c);
	token->s = process;
	token->next = NULL;
	if (!*p_token)
		*p_token = token;
	else
	{
		curr = ft_get_tail(*p_token);
		curr->next = token;
	}
	printf("add_token = _%s_\n", token->s);
}

void	add_pipe(t_list **p_token)
{	
	t_list	*curr;
	t_list	*token;

	if(!p_token || !*p_token)
		return;
	token = ft_malloc(sizeof(t_list));
	token->s = ft_strdup("|");
	token->next = NULL;
	printf("add_pipe = _%s_\n", token->s);
	if (!*p_token)
		*p_token = token;
	else
	{
		curr = ft_get_tail(*p_token);
		curr->next = token;
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
