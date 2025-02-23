/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:20:24 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 02:59:57 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_redir(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && (ft_cop(token->s) != 1))
	{
		if (ft_cop(token->s) > 1)
		{
			i += 2;
			token = token->next;
		}	
		token = token->next;
	}
	return (i);
}

int	ft_redir_out(t_token *token, int fd[], int *i_fd)
{
	printf("redir out\n");
	fd[*i_fd] = open(token->next->s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_in(t_token *token, int fd[], int *i_fd)
{
	printf("redir in\n");
	fd[*i_fd] = open(token->next->s, O_RDONLY);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdin\n", -1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_append(t_token *token, int fd[], int *i_fd)
{
	printf("redir append\n");
	fd[*i_fd] = open(token->next->s, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}


int	ft_mod_fd(t_token *token, int fd[], int *i_fd)
{
	int	cop;

	cop = ft_cop(token->s);
	if (cop == 2)
		return (ft_redir_out(token, fd, i_fd));
	else if (cop == 3)
		return (ft_redir_in(token, fd, i_fd));
	else if (cop == 4)
	        return (ft_redir_append(token, fd, i_fd));
	/*
	else if (ft_cop(cmd->params[i]) == 5)
	{
		return (ft_heredoc(cmd, i, fd, i_fd));
	}
*/
	return (0);
}

int	ft_bckp_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		return (ft_perror("redirect: bckup fd\n", 1));
	}
	return (0);
}

void	ft_close_fd(int fd[], int i_fd)
{
	int j;

	j = 3;
	while(j < i_fd)
	{
		close(fd[j]);
		j++;
	}
}

void	ft_restore_fd(int fd[])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int	ft_get_redir(t_token *head, int *fd, int *count)
{
	int		r;
	int		i_fd;
	t_token	*token;

	token = head;
	*count = ft_count_redir(token) + 3;
	fd = ft_malloc(sizeof(int) * (*count));
	if (ft_bckp_fd(fd) != 0)
		return (ft_perror("error: saving std fds\n", -1));
	i_fd = 3;
	while(token)
	{
		r = ft_mod_fd(token, fd, &i_fd);
		if (r == -1)
			return (-1);
		token = token->next;
	}
	ft_close_fd(fd, i_fd);
	return (i_fd);
}
