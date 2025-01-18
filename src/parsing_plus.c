/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:32 by atambo            #+#    #+#             */
/*   Updated: 2025/01/17 23:55:10 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_count	*ft_counter(void)
{
	t_count	*c;

	c = ft_malloc(sizeof(t_count));
	c->i = 0;
	c->j = 0;
	c->k = 0;
	c->last = 0;
	c->q = 0;
	c->temp = 0;
	c->aux = 0;
	return (c);
}

t_list	*add_token(char *line, t_list **p_token, t_count **p_c)
{
	t_list	*token;
	t_count	*c;
	char	*process;

	token = *p_token;
	c = *p_c;
	token->s = ft_malloc(sizeof(char *) * (c->temp));
	ft_strlcpy(token->s, &line[c->last], c->temp);
	process = ft_get_token_2(token->s, c);
	token->s = process;
	token->next = ft_malloc(sizeof(t_list));
	token = token->next;
	token->next = NULL;
	return (token);
}

t_list	*add_pipe(t_list **p_token)
{
	t_list	*token;

	token = *p_token;
	token->s = ft_strdup("|");
	token->next = ft_malloc(sizeof(t_list));
	token = token->next;
	token->next = NULL;
	return (token);
}

void	skip_spaces(char *line, t_count **p_c)
{
	t_count	*c;

	c = *p_c;
	while (line[c->k] == ' ')
		(c->k)++;
}
