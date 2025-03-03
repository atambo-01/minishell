/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:24:04 by atambo            #+#    #+#             */
/*   Updated: 2025/03/03 12:33:09 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token *ft_get_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	if (ft_cop(token->s) == 1)
		token = token->next;
	while(token)
	{
		if (ft_cop(token->s) == 1)
			return(token);
		token = token->next;
	}
	return(NULL);
}

int	ft_handle_first_fork(t_main_vars* mv, t_cmd *cmd, int *fd, t_token *token)
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
		if (ft_count_redir(token))
			ft_get_redir(token, &(mv->fd), &(mv->fd_c));
		exit(ft_execute(cmd));
	}
	return (pid);
}


int	ft_handle_second_fork(t_main_vars *mv, t_cmd *cmd, int *fd, t_token *token)
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
		if (ft_get_pipe(token) != NULL)
			exit(ft_pipe(mv, cmd, token));
		else 
		{	
			if (ft_count_redir(token))
				ft_get_redir(token, &(mv->fd), &(mv->fd_c));
			exit(ft_execute(cmd));
		}
	}
	return(pid);
}

int	ft_pipe(t_main_vars *mv, t_cmd *cmd, t_token *token)
{
	int	fd[2];
	int	status;
	pid_t	pid_0;
	pid_t	pid_1;

	status = -1;
	pid_0 = 0;
	pid_1 = 0;
	if (pipe(fd) == -1)
		return(ft_perror("minishell: pipe fd error\n", 1));
	pid_0 = ft_handle_first_fork(mv, cmd, fd, token);
	token = ft_get_pipe(token);
	pid_1 = ft_handle_second_fork(mv, cmd->nc->nc, fd, token);
	ft_restore_fd(mv->fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_0, &status, 0);
	waitpid(pid_1, &status, 0);
	return(status);
}
