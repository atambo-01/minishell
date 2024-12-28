/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:31:03 by eneto             #+#    #+#             */
/*   Updated: 2024/12/25 17:22:49 by eneto            ###   ########.fr       */
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
        printf("%s%s%s", " ", phrase, "\n");
    }
    return;
}