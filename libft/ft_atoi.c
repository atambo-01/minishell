/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:57:59 by atambo            #+#    #+#             */
/*   Updated: 2024/05/19 17:24:07 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr ++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr ++;
	}
	else if (*nptr == '+')
		nptr ++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + ((char)(*nptr) - '0');
		if ((res * sign > 2147483647) || (res * sign < -2147483648))
			return (0);
		nptr ++;
	}
	return ((int)(res * sign));
}
