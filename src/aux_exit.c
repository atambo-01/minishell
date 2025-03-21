/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:43 by eneto             #+#    #+#             */
/*   Updated: 2025/03/21 16:39:21 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_convert(long long l)
{
	if (l < 0)
		return (256 + (int)(l % 256));
	else if (l > 255)
		return ((int)(l % 256));
	return ((int)l);
}

void	handle_sign(char *str, t_count *c)
{
	if (str[c->i] == '-' || str[c->i] == '+')
	{
		c->j = 1;
		if (str[c->i] == '-')
			c->j = -1;
		c->i++;
	}
	return ;
}

int	handle_quotes(char *str, t_count *c)
{
	if (str[c->i] == '"' || str[c->i] == '\'')
	{
		if (c->k == 0)
			c->k = str[c->i];
		else if (c->k == str[c->i])
			c->k = 0;
		else
			return (1);
		(c->i)++;
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}
