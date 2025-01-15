/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:06:42 by eneto             #+#    #+#             */
/*   Updated: 2025/01/15 07:53:48 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	verifyp(t_pipe *command)
{
	if (pipe(command->fd) == -1)
	{
		perror("Erro na criação do pipe");
		exit(1);
	}
	command->pid = fork();
	if (command->pid == -1)
	{
		printf("%s%s", "Erro na leitura do comando", command->c0);
		exit(1);
	}
	return;
}


int	pipes(t_pipe *command)
{
	verifyp(command);
	if (command->pid == 0)
	{
		close(command->fd[1]);
		dup2(command->fd[0], STDIN_FILENO);
		close(command->fd[0]);
		execve(command->c0[0], command->c0, NULL);
		printf("%s%s", "Erro na leitura do comando", command->c0);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(command->fd[0]);
		dup2(command->fd[1], STDOUT_FILENO);
		close(command->fd[1]);
		execve(command->c1[0], command->c1, NULL);
		printf("%s%s", "Erro na leitura do comando", command->c1);
		exit(EXIT_FAILURE);
	}
	close(command->fd[0]);
	close(command->fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
