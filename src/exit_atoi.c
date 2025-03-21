/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 02:59:16 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:40:42 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	handle_numbers(char *str, t_count *c)
{
	while (ft_isdigit(str[c->i]) || is_quote(str[c->i]))
	{
		if (is_quote(str[c->i]))
		{
			if (handle_quotes(str, c) != 0)
				return (-1);
			continue ;
		}
		c->l = c->l * 10 + (str[c->i] - '0');
		(c->i)++;
	}
	while (is_quote(str[c->i]) || is_space(str[c->i]))
	{
		if (handle_quotes(str, c) != 0)
			return (-1);
		else if (is_space(str[c->i]))
			(c->i)++;
	}
	if (str[c->i] != 0)
		return (-1);
	return (0);
}

int	ft_check_number(char *str)
{
	int		i;
	char	*sign;

	i = 0;
	sign = ft_strchr(str, '-');
	while (*str)
	{
		if (ft_isdigit(*str))
		{	
			i++;
			if (i > ft_strlen("9223372036854775807"))
				return (-1);
			if (i == ft_strlen("9223372036854775807"))
			{	
				if (sign == NULL && *str > '7')
					return (-1);
				if (sign != NULL && *str > '8')
					return (-1);
			}
		}	
		str++;
	}
	return (i);
}

int	ft_exit_atoi(char *str)
{
	t_count	c;

	ft_counter(&c);
	if (!str || !*str || ft_check_number(str) <= 0)
		return (-1);
	c.j = 1;
	while (is_quote(str[c.i]) || is_space(str[c.i]))
	{
		if (handle_quotes(str, &c) != 0)
			return (-1);
		else if (is_space(str[c.i]))
			(c.i)++;
	}
	handle_sign(str, &c);
	if (handle_numbers(str, &c) != 0)
		return (-1);
	return (ft_convert((c.j / abs(c.j)) * c.l));
}
