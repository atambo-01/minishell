/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:14:05 by eneto             #+#    #+#             */
/*   Updated: 2025/03/22 12:49:29 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
o_int	1 main
o_int	2 execve
o_int	3 builtins
o_int	4 heredoc
-----------------------------------
o_quit	1 main
o_quit	2 execve
o_quit	3 execve
*/

void	ft_signal(int o_int, int o_quit)
{
	if (o_int < 0)
		signal(SIGINT, SIG_DFL);
	else if (o_int == 0)
		signal(SIGINT, SIG_IGN);
	else if (o_int == 1)
		signal(SIGINT, ft_ctrl_c);
	else if (o_int == 2)
		signal(SIGINT, ft_execve_sigint);
	else if (o_int == 3)
		signal(SIGINT, ft_builtin_sigint);
	else if (o_int == 4)
		signal(SIGINT, ft_heredoc_sigint);
	if (o_quit < 0)
		signal(SIGQUIT, SIG_DFL);
	else if (o_quit == 0)
		signal(SIGQUIT, SIG_IGN);
	else if (o_quit == 1)
		signal(SIGQUIT, SIG_IGN);
	else if (o_quit == 2)
		signal(SIGQUIT, ft_execve_sigquit);
}
