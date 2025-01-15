/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:32:29 by atambo            #+#    #+#             */
/*   Updated: 2025/01/05 23:54:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	j = 0;
	while (big[j] && j < len)
	{
		i = 0;
		while (little[i] && (j + i) < len && big[j + i] == little[i])
		{
			i++;
		}
		if (little[i] == '\0')
			return ((char *)&big[j]);
		j++;
	}
	return (NULL);
}
