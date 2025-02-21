/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:46 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 17:34:10 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_redir_out(t_cmd *cmd, int i, int fd[], int *i_fd)
{
	fd[*i_fd] = open(cmd->redir[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_in(t_cmd *cmd, int i, int fd[], int *i_fd)
{
	fd[*i_fd] = open(cmd->redir[i + 1], O_RDONLY);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdin\n", -1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_append(t_cmd *cmd, int i, int fd[], int *i_fd)
{
	fd[*i_fd] = open(cmd->redir[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}

int	count_redir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
		i++;
	return (i);
}

int	ft_redirect(t_cmd *cmd)
{
	int	*fd;
	int	r;
	int	i;
	int	i_fd;
	int	status;

	if (!cmd->redir)
		return (1);
	fd = ft_malloc(sizeof(int) * (count_redir(cmd) + 1));
	if (bckp_fd(fd) != 0)
		return (ft_perror("error: saving std fds\n", -1));
	i = 0;
	i_fd = 3;
	while (cmd->redir[i])
	{
		r = mod_fd(cmd, i, fd, &i_fd);
		if (r == -1)
			return (-1);
		i++;
	}
	status = ft_execute(cmd, 0, 0);
	close_fd(fd, i_fd);
	return (status);
}
