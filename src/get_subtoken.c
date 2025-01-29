/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subtoken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:51:03 by atambo            #+#    #+#             */
/*   Updated: 2025/01/29 17:42:41 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_subtoken_handle_quotes(char *old, char *new, t_count *c)
{
	if (old[c->i] == c->q && ft_strchr(old + c->i + 1, c->q))
	{
		c->i += 1;
		while (old[c->i] != c->q)
		{
			//  if (q == '"' && (old == '$' || old[k] == '\\') )
			//  ft_expand(old + i, new);
			new[(c->k)] = old[(c->i)];
			(c->k)++;
			(c->i)++;
		}
		c->i += 1;
	}
	else if (c->q == '"')
		c->q = '\'';
	else
	{
		new[(c->k)] = old[(c->i)];
		c->q = '"';
		(c->k)++;
		(c->i)++;
	}
}

char	*ft_get_subtoken(char *old)
{
	char	*new;
	t_count	*c;

	c = ft_malloc(sizeof(t_count));
	ft_counter(&c);
	c->q = '"';
	new = ft_malloc(sizeof(char) * ft_strlen(old) + 1);
	while (old[c->i])
		ft_subtoken_handle_quotes(old, new, c);
	free(old);
	old = NULL;
	free(c);
	c = NULL;
	return (new);
}
