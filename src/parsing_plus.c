/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/01/21 18:50:22 by atambo           ###   ########.fr       */
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


t_list	*add_token(char *line, t_list **p_token, t_count **p_c)
{
	t_list	*token;
	t_count	*c;
	char	*process;
	
	token = NULL;
	if (!line || !p_c)
		return(NULL);
	if (!*p_token)
	{
		token = ft_malloc(sizeof(t_list));
	}
	else
		token = *p_token;
	c = *p_c;
	token->s = ft_malloc(sizeof(char *) * (c->temp + 1));
	printf("HERE - 2!\n");
	ft_strlcpy(token->s, &line[c->last], c->temp + 1);
	process = ft_get_token_2(token->s, c);
//	ft_free_p((void **)&(token->s));
	token->s = process;
	token->next = ft_malloc(sizeof(t_list));
	token = token->next;
	token->next = NULL;
	return (token);
}

t_list	*add_pipe(t_list **p_token)
{
	t_list	*token;

	if(!p_token || !*p_token)
	token = *p_token;
	token->s = ft_strdup("|");
	if (!token->s)
		return(NULL);
	token->next = ft_malloc(sizeof(t_list));
	token = token->next;
	token->next = NULL;
	return (token);
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
