/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subtoken.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:51:03 by atambo            #+#    #+#             */
/*   Updated: 2025/02/28 16:23:17 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_subtoken(char *old)
{
	char	*new;
	t_count	c;

	ft_counter(&c);
	new = ft_malloc(sizeof(char) * ft_strlen(old) + 1);
	while (old[c.i])
	{
		if (old[c.i] == '"' || old[c.i] == '\'')
		{
			c.q = old[c.i];
			c.i++;
			while(old[c.i] && old[c.i] != c.q)
			{
				new[c.k] = old[c.i];
				c.i++;
				c.k++;
			}
			c.i++;
		}
		else
		{
			new[c.k] = old[c.i];
			c.i++;
			c.k++;
		}
	}
	return (new);
}
