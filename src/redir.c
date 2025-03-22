/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:20:24 by atambo            #+#    #+#             */
/*   Updated: 2025/03/22 16:06:37 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_redir_out(t_token *token, int fd[], int *i_fd)
{
	char	*temp;
	temp = ft_get_subtoken(token->next->s);
	fd[*i_fd] = open(token->next->s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("minishell: error redirecting stdout\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_in(t_token *token, int fd[], int *i_fd)
{
	char	*temp;

	temp = ft_get_subtoken(token->next->s);
	fd[*i_fd] = open(temp, O_RDONLY);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 1));
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdin\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_append(t_token *token, int fd[], int *i_fd)
{
	char	*temp;

	temp = ft_get_subtoken(token->next->s);
	fd[*i_fd] = open(temp, O_RDONLY);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 1));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_get_redir(t_main_vars *mv, t_token *head, int **fd, int *count)
{
	int		r;
	int		i_fd;
	t_token	*token;

	token = head;
	*count = ft_count_redir(token);
	if (*count == 0)
		return (0);
	else
		*count += 3;
	i_fd = 3;
	while (token && ft_cop(token->s) != 1)
	{
		ft_signal(0, 0);
		r = ft_mod_fd(mv, token, *fd, &i_fd);
		if (r)
			return (r);
		token = token->next;
	}
	ft_close_fd(*fd, i_fd);
	return (0);
}
