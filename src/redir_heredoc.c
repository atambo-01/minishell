/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:08:35 by atambo            #+#    #+#             */
/*   Updated: 2025/03/22 16:31:02 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_lines(int fd[], int i_fd, char **line)
{
	write(fd[i_fd + 1], *line, strlen(*line));
	write(fd[i_fd + 1], "\n", 1);
	free(*line);
}

int	heredoc_set_status(void)
{
	printf("signal = %d\n", g_signal);
	if (g_signal == SIGINT)
		return (130);
	else
		return (0);
}

void	heredoc_child(t_main_vars *mv, int fd[], int i_fd, char *delimiter)
{
	char	*line;
	char	*temp;

	ft_signal(-1, 0);
	close(fd[i_fd]);
	while (1)
	{
		temp = readline("> ");
		line = ft_expand(temp, mv->env, mv->exit, 1);
		free(temp);
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				ft_perror(HEREDOC_1, 1);
			free(line);
			break ;
		}
		write_lines(fd, i_fd, &line);
	}
	close(fd[i_fd + 1]);
	free(delimiter);
	exit(EXIT_SUCCESS);
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
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1 && g_signal != SIGINT)
		status = (ft_perror("minshell: heredoc: dup2\n", 1));
	(*i_fd) += 2;
	return (status);
}
