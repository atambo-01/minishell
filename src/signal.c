/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:14:05 by eneto             #+#    #+#             */
/*   Updated: 2025/03/01 02:49:27 by atambo           ###   ########.fr       */
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

void	ft_ctrl_d(t_main_vars *mv)
{
	if (mv->line == NULL)
	{
		write(1, "exit\n", 5);
		// ft_minishell_exit(&sig);
		exit(1);
	}
	return ;
}

void	ft_signal(int opt[])
{
	if (opt[0])
		signal(SIGQUIT, SIG_IGN); //main
	if (opt[1])
		signal(SIGINT, ft_ctrl_c); //main
	if (opt[2])
		signal(SIGQUIT, ft_execve_sigquit); //execve
	if (opt[3])
		signal(SIGQUIT, ft_execve_sigquit_2); //execve
	if (opt[4])
		signal(SIGINT, ft_execve_sigint); //execve
	if (opt[5])
		signal(SIGINT, ft_builtin_int); //builtins
}

