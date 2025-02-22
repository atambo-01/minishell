/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:14:05 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 23:59:38 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = SIGINT;
}

void	ctrl_d(t_main_vars *sig)
{
	g_signal = 0;
	if (sig->line == NULL)
	{
		write(1, "exit\n", 5);
		// ft_minishell_exit(&sig);
		exit(1);
	}
	return ;
}

void    ft_signal(int opt[])
{
    if (opt[0])
        signal(SIGQUIT, SIG_IGN);
    if (opt[1])
        signal(SIGINT, ctrl_c);
    if (opt[2])
        signal(SIGQUIT, ft_execve_sigquit);
    if (opt[3])
        signal(SIGQUIT, ft_execve_sigquit_2);
    if (opt[4])
        signal(SIGINT, ft_execve_sigint);
	if (opt[5])
		signal(SIGINT, ft_builtin_int);
}

