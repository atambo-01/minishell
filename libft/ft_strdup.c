/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:55:51 by atambo            #+#    #+#             */
/*   Updated: 2025/01/20 23:54:00 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	size_t	n;
	char	*dst;
	
	if (!src)
		return(NULL);
	n = 0;
	while (src[n])
		n ++;
	dst = malloc((n + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	n = 0;
	while (src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (dst);
}
