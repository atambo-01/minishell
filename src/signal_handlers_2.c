/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:40:02 by atambo            #+#    #+#             */
/*   Updated: 2025/03/22 12:51:27 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_builtin_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

void ft_heredoc_sigint(int sig)
{
    g_signal = sig;              // Set global signal flag
    rl_replace_line("", 0);      // Clear current input
    rl_done = 1;                 // Tell readline to finish
    write(STDOUT_FILENO, "\n", 1);  // Newline for clean exit
}
