/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:38:20 by atambo            #+#    #+#             */
/*   Updated: 2024/05/21 14:20:46 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	max;

	max = 4294967295;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > max / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}
