/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:43:41 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 17:56:02 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execve_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_execve_sigquit(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5);
	exit(0);
}

void	ft_execve_sigquit_2(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5);
}

int	bckp_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		return (1);
	}
	return (0);
}
