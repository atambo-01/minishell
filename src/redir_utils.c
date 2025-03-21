/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:47:56 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:00:30 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_redir(t_token *token)
{
	int		i;
	t_token	*curr;

	i = 0;
	if (!token)
		return (0);
	curr = token;
	while (curr && (ft_cop(curr->s) != 1))
	{
		if (ft_cop(curr->s) > 1)
		{
			if (curr->next)
				i++;
		}
		if (curr)
			curr = curr->next;
	}
	return (i);
}

int	ft_mod_fd(t_main_vars *mv, t_token *token, int fd[], int *i_fd)
{
	int	cop;

	cop = ft_cop(token->s);
	if (cop == 2)
		return (ft_redir_out(token, fd, i_fd));
	else if (cop == 3)
		return (ft_redir_in(token, fd, i_fd));
	else if (cop == 4)
		return (ft_redir_append(token, fd, i_fd));
	else if (cop == 5)
		return (ft_heredoc(mv, token, fd, i_fd));
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
		return (ft_perror("minishell: redirect: bckup fd\n", 1));
	}
	return (0);
}

void	ft_close_fd(int fd[], int i_fd)
{
	int	j;

	j = 3;
	while (j < i_fd)
	{
		close(fd[j]);
		j++;
	}
}

void	ft_restore_fd(int fd[])
{
	if (!fd)
		return ;
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}
