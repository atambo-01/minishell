/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:24:04 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 01:20:09 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_handle_first_fork(t_cmd *cmd, int *fd)
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

int	ft_handle_second_fork(t_cmd *cmd, int *fd)
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
		exit(ft_perror("pipe", EXIT_FAILURE));
	pid_0 = ft_handle_first_fork(cmd, fd);
	pid_1 = ft_handle_second_fork(cmd, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_0, &status, 0);
	waitpid(pid_1, &status, 0);
	return(status);
}
