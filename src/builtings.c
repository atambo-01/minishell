/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:31:03 by eneto             #+#    #+#             */
/*   Updated: 2025/01/06 10:23:22 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void echo(char *phrase)
{
    char *ech = "echo";
    
    while(phrase == ech)
            phrase++;
    if(phrase != ech)
    {
        printf("%s%s", " ", phrase, "\n");
    }
    return;
}
