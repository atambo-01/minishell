/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:19:53 by atambo            #+#    #+#             */
/*   Updated: 2025/01/31 14:16:40 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_first_fork(t_cmd *cmd, int *fd, const int prev_exit)
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
		ft_execute(cmd->pc, 1, prev_exit);
	}
}

int	handle_second_fork(t_cmd *cmd, int *fd, const int prev_exit)
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
		ft_execute(cmd->nc, 0, prev_exit);
	}
}

int	ft_pipe(t_cmd *cmd, const int prev_exit)
{
	int	fd[2];
	int	status;

	status = -1;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	status = handle_first_fork(cmd, fd, prev_exit);
	status = handle_second_fork(cmd, fd, prev_exit);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return(status);
}
