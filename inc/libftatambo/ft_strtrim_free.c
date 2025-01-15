/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:50:30 by root              #+#    #+#             */
/*   Updated: 2025/01/05 23:50:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set ++;
	}
	return (0);
}

char	*ft_strtrim_free(char *s1, char const *set)
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
	end = ft_strlen(s1);
	while (end > start && in_set(s1[end - 1], set))
		end --;
	ts = (char *)malloc((end - start + 1) * sizeof(char));
	if (!ts)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		ts[i] = s1[start + i];
		i ++;
	}
	ts[i] = '\0';
	free(s1);
	return (ts);
}
