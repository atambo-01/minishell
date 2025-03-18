/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:14:05 by eneto             #+#    #+#             */
/*   Updated: 2025/03/09 22:47:20 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_signal(int opt[])
{
	if (opt[0] == 1)
		signal(SIGQUIT, SIG_IGN); //main
	if (opt[1] == 1)
		signal(SIGINT, ft_ctrl_c); //main
	if (opt[2] == 1)
		signal(SIGQUIT, ft_execve_sigquit); //execve
	if (opt[3] == 1)
		signal(SIGQUIT, ft_execve_sigquit_2); //execve
	if (opt[4] == 1)
		signal(SIGINT, ft_execve_sigint); //execve
	if (opt[5] == 1)
		signal(SIGINT, ft_builtin_int); //builtins
	if (opt[6] == 1)
		signal(SIGINT, ft_heredoc_sigint);
	if (!opt[1] && !opt[4] && !opt[5] && !opt[6])
		signal(SIGINT, SIG_IGN);
}
