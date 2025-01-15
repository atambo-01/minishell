/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:54:15 by atambo            #+#    #+#             */
/*   Updated: 2024/05/22 14:02:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	asign(char *result, int digits, int n, int i)
{
	if (n < 0)
	{
		result[i++] = '-';
		n = -n;
	}
	result[digits] = '\0';
	while (digits > i)
	{
		result[digits - 1] = (n % 10) + '0';
		n /= 10;
		digits--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		digits;
	char	*result;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = ft_count_digits(n);
	if (n < 0)
		digits++;
	result = (char *)malloc((digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	asign(result, digits, n, i);
	return (result);
}
