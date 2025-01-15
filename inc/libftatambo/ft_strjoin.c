/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:02:47 by atambo            #+#    #+#             */
/*   Updated: 2024/05/21 18:03:39 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s;
	int		j;
	int		i;
	char	*s12;

	s = ft_strlen(s1) + ft_strlen(s2);
	s12 = (char *)malloc((s + 1) * sizeof(char));
	if (!s12)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s12[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j])
	{
		s12[i + j] = s2[j];
		j ++;
	}
	s12[i + j] = '\0';
	return (s12);
}
