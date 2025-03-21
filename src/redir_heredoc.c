/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:08:35 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 15:16:31 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_child(t_main_vars *mv, int fd[], int i_fd, char *delimiter)
{
	char	*line;
	char	*temp;

	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(ft_perror("minishell : dup2 failed in heredoc child", 1));
	ft_signal(0, 0);
	close(fd[i_fd]);
	while (g_signal != SIGINT)
	{
		temp = readline("> ");
		line = ft_expand(temp, mv->env, mv->exit, 1);
		free(temp);
		if (!line || g_signal == SIGINT || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[i_fd + 1], line, strlen(line));
		write(fd[i_fd + 1], "\n", 1);
		free(line);
	}
	close(fd[i_fd + 1]);
	free(delimiter);
	exit(0);
}

int	ft_heredoc(t_main_vars *mv, t_token *token, int fd[], int *i_fd)
{
	pid_t	pid;
	int		status;
	char	*temp;

	temp = ft_get_subtoken(token->next->s);
	status = 0;
	if (pipe(&fd[*i_fd]) == -1)
		return (ft_perror("minshell: heredoc: pipe\n", 1));
	pid = fork();
	if (pid == -1)
		return (ft_perror("minshell: heredoc: fork\n", 1));
	if (pid == 0)
		heredoc_child(mv, fd, *i_fd, temp);
	free(temp);
	close(fd[*i_fd + 1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		status = (130);
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1 && g_signal != SIGINT)
		status = (ft_perror("minshell: heredoc: dup2\n", 1));
	(*i_fd) += 2;
	return (status);
}
