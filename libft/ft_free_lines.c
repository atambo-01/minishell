/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:03:38 by atambo            #+#    #+#             */
/*   Updated: 2025/01/18 17:04:32 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int ft_free_lines(char ***lines)
{
    int count = 0;

    if (lines && *lines)
    {
        while ((*lines)[count])
        {
            free((*lines)[count]);
            count++;
        }
        free(*lines);
        *lines = NULL;
    }
    return count;
}
