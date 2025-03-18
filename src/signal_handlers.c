/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:40:19 by atambo            #+#    #+#             */
/*   Updated: 2025/03/09 23:01:58 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_ctrl_c(int sig)
{
 	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_execve_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

void	ft_execve_sigquit(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
	exit(0);
}

void	ft_execve_sigquit_2(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5);
	g_signal = SIGQUIT;
}

void	ft_builtin_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

void	ft_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
	exit(0);
}
