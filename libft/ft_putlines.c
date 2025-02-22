/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:55:26 by atambo            #+#    #+#             */
/*   Updated: 2025/01/20 23:07:10 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_putlines(char **lines)
{
	int	i;
	int	f;

	f = 0;
	if(!lines || !*lines)
		return(0);
	while(lines[f])
		f++;
	i = 0;
	while(i < f && lines[i])
	{
		ft_putstr(lines[i]);
		ft_putstr("\n");
		i++;
	}
	return(i);
}
