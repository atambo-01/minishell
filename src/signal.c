/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:14:05 by eneto             #+#    #+#             */
/*   Updated: 2025/03/21 00:20:33 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_signal(int o_int, int o_quit)
{
	if 		(o_int == 1)
		signal(SIGINT, ft_ctrl_c); //main
	else if (o_int == 2)
		signal(SIGINT, ft_execve_sigint); //execve
	else if (o_int == 3)
		signal(SIGINT, ft_builtin_sigint); //builtins
	else
		signal(SIGINT, SIG_DFL);

	if 		(o_quit == 1)
		signal(SIGQUIT, SIG_IGN); //main
	else if (o_quit == 2)
		signal(SIGQUIT, ft_execve_sigquit_2); //execve
	else if (o_quit == 3)
		signal(SIGQUIT, ft_execve_sigquit); //execve
	else
		signal(SIGQUIT, SIG_DFL);
}
