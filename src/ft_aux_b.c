/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:38:04 by eneto             #+#    #+#             */
/*   Updated: 2025/03/07 07:41:52 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_strstr(char *str, char *str_find)
{
    int i;
    int j;

    i = 0;
    while(str[i])
    {
        j = 0;
        while(str[i + j] == str_find[j])
        {
            if (!str_find[j + 1])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}