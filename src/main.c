/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:09:36 by eneto             #+#    #+#             */
/*   Updated: 2024/12/19 18:09:36 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void)
{
    char *prompt;
    char *echos = "echo";

    while (1)
    {
        prompt = (readline("minishell$"));
        add_history(prompt);
        if (echos)
            echo(prompt);
    }
    return (0);
}
