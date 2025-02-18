/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:19:53 by atambo            #+#    #+#             */
/*   Updated: 2025/02/18 12:52:09 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_first_fork(t_cmd *cmd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execute(cmd->pc, 0, 1);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	handle_second_fork(t_cmd *cmd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		ft_execute(cmd->nc, 1, 1);
		exit(EXIT_FAILURE);
	}
	return(pid);
}

int	ft_pipe(t_cmd *cmd)
{
	int	fd[2];
	int	status;
	pid_t	pid_0;
	pid_t	pid_1;

	status = -1;
	pid_0 = 0;
	pid_1 = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_0 = handle_first_fork(cmd, fd);
	pid_1 = handle_second_fork(cmd, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_0, &status, 0);
	waitpid(pid_1, &status, 0);
	return(status);
}