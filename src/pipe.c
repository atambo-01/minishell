/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:06:42 by eneto             #+#    #+#             */
/*   Updated: 2025/01/15 12:23:35 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void  ft_pipe(t_cmd *cmd)
{
	int 	fd[2];
	t_pid	pid1;
	t_pid	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		// Child process 1: Execute the command before the pipe
		dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the pipe's write end
		close(fd[0]);              // Close unused read end
		close(fd[1]);
		execute(cmd->pc);              // Execute the previous command
	}
	pid_t pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		// Child process 2: Execute the command after the pipe
		dup2(fd[0], STDIN_FILENO); // Redirect stdin to the pipe's read end
		close(fd[1]);              // Close unused write end
		close(fd[0]);
		execute(cmd->nc);              // Execute the next command
	}
	// Parent process: Close pipe ends and wait for children
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
