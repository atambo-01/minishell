/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:24:04 by atambo            #+#    #+#             */
/*   Updated: 2025/02/26 00:55:15 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_handle_child(t_main_vars *mv, int *fd, t_token *token)
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
		if (token != mv->token)
			dup2(fd[0], STDIN_FILENO);
		if (ft_get_pipe(token))
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (ft_count_redir(token) > 0)
			ft_get_redir(token, &mv->fd, &(mv->fd_c));
		mv->exit = ft_execute(mv->cmd);
		ft_restore_fd(mv->fd);
		exit(EXIT_FAILURE);
	}
	return(pid);
}

t_token *ft_get_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	while(token)
	{
		if (ft_cop(token->s) == 1)
			return(token);
		token = token->next;
	}
	return(NULL);
}

int	ft_pipe(t_main_vars *mv, t_cmd *cmd, t_token *head)
{
	t_token	*token;
	pid_t	pid;
	int		fd[2];
	int		status;

	pid = 0;
//	token = NULL;
	status = 0;
	if (pipe(fd) == -1)
		exit(ft_perror("ft_pipe", EXIT_FAILURE));
//	else if (!token)
//		exit(ft_perror("ft_pipe: token", EXIT_FAILURE));
	token = mv->token;
	while(token)
	{
		pid = ft_handle_child(mv, fd, token);
		if (cmd->nc)
		{
			if (cmd->nc->nc)
				cmd = cmd->nc->nc;
			else
				break;
		}
		else
		{
			break;
		}
		token = ft_get_pipe(token);
	}
	return(status);
}

