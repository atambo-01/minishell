/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:24:41 by atambo            #+#    #+#             */
/*   Updated: 2025/01/24 15:05:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*ts;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start ++;
	if (s1[start] == 0)
		return(NULL);
	end = ft_strlen(s1);
	while (end > start && in_set(s1[end - 1], set))
		end --;
	ts = ft_malloc((end - start + 1) * sizeof(char));
	i = 0;
	while (start + i < end)
	{
		ts[i] = s1[start + i];
		i ++;
	}
	ts[i] = '\0';
	return (ts);
}
