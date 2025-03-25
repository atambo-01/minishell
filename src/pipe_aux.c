/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:25 by atambo            #+#    #+#             */
/*   Updated: 2025/03/23 15:14:05 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pipe_child_aux(t_pipe_data *data)
{
	int	i;
	int	cmd_count;

	cmd_count = data->cmd_count;
	i = data->i;
	if (i == 0 && cmd_count > 1)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (i > 0 && i < cmd_count - 1)
	{
		dup2(data->prev_read_fd, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->prev_read_fd);
	}
	else if (i == cmd_count - 1 && cmd_count > 1)
	{
		dup2(data->prev_read_fd, STDIN_FILENO);
		close(data->prev_read_fd);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	return (0);
}

void	ft_pipe_child(t_main_vars *mv, t_cmd *curr, t_pipe_data *data)
{
	int	status;

	status = ft_pipe_child_aux(data);
	if (status == 0)
	{
		status = ft_count_redir(data->token);
		if (status > 0)
		{	
			status = ft_get_redir(mv, data->token, &(mv->fd), &(mv->fd_c));
			if (status == 0)
				status = ft_execute(curr);
		}
		else
			status = ft_execute(curr);
	}
	exit(status);
}

int	ft_count_cmd(t_cmd *cmd)
{
	int		count;
	t_cmd	*curr;

	count = 0;
	curr = cmd;
	while (curr)
	{
		if (ft_cop(curr->n) == 0)
			count++;
		curr = curr->nc;
	}
	return (count);
}

t_token	*ft_do_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	if (ft_cop(token->s) == 1)
		token = token->next;
	while (token)
	{
		if (ft_cop(token->s) == 1)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}
