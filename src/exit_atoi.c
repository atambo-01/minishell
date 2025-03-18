/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:04:46 by atambo            #+#    #+#             */
/*   Updated: 2025/03/18 11:33:42 by atambo           ###   ########.fr       */
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

int	handle_space_and_signs(char *str, t_count *c)
{
	if (str[c->i] == ' ' || str[c->i] == '\t')
	{
		while (str[c->i] == ' ' || str[c->i] == '\t')
			c->i++;
		if (str[c->i + 1])
		{
			if (str[c->i] == 0)
				return(1);
		}
	}
	else if (str[c->i] == '-' || str[c->i] == '+')
	{
		if (c->j != 1)
			return (-1);
		c->j = 2;
		if (str[c->i] == '-')
			c->j = -2;
		c->i++;
	}
	else
		return (0);
	return (1);
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
			return (-1);
		(c->i)++;
	}
	else
		return (handle_space_and_signs(str, c));
	return (1);
}

int	handle_number(char *str, t_count *c)
{
	if (isdigit(str[c->i]))
	{
		c->l = c->l * 10 + (str[c->i] - '0');
		if (c->l > 9223372036854775806)
			return (-1);
		c->i++;
		return (1);
	}
	return (0);
}

int 	ft_has_digit(char *str)
{
	while(*str)
	{
		if (*str >= '0' && *str <= '9')
			return (1);
		str++;
	}
	return(0);
}

int ft_exit_atoi(char *str)
{
	int		processed;
	t_count	c;

	ft_counter(&c);
	if (!str || !*str || ft_has_digit(str) == 0)
		return (-1);
	c.j = 1;
	while (str[c.i])
	{
		processed = handle_quotes(str, &c);
		if (processed == -1)
			return (-1);
		if (processed == 0) 
		{
			processed = handle_number(str, &c);
			if (processed == -1)
				return (-1);
			if (processed == 0)
				return (-1);
		}
	}
	return (ft_convert((c.j / abs(c.j)) * c.l));
}
