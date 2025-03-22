/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:24:04 by atambo            #+#    #+#             */
/*   Updated: 2025/03/22 16:21:53 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipe_parent(t_pipe_data *data)
{
	int	i;
	int	cmd_count;

	cmd_count = data->cmd_count;
	i = data->i;
	if (i > 0)
		close(data->prev_read_fd);
	if (i < cmd_count - 1)
	{
		close(data->fd[1]);
		data->prev_read_fd = data->fd[0];
	}
}

int	ft_wait_children(t_pipe_data *data, int status)
{
	int	j;

	j = 0;
	while (j < data->i)
	{
		waitpid(data->pids[j], &status, 0);
		j++;
		if (status)
			return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

int	ft_init_pipe(t_main_vars *mv, t_pipe_data *data, t_cmd **curr, int *status)
{
	data->token = mv->token;
	*curr = mv->cmd;
	*status = 0;
	data->i = 0;
	data->prev_read_fd = -1;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->cmd_count = ft_count_cmd(mv->cmd);
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
	{
		ft_perror("minishell: malloc error\n", 1);
		return (1);
	}
	return (0);
}

int	ft_pipe(t_main_vars *mv)
{
	t_cmd		*curr;
	int			status;
	t_pipe_data	data;

	if (ft_init_pipe(mv, &data, &curr, &status) == 1)
		return (1);
	while (curr && data.i < data.cmd_count)
	{
		if (data.i < data.cmd_count - 1 && pipe(data.fd) == -1)
			return (ft_perror("minishell: pipe fd error\n", 1));
		data.pids[data.i] = fork();
		if (data.pids[data.i] == -1)
			return (ft_perror("minishell: fork error\n", 1));
		if (data.pids[data.i] == 0)
			ft_pipe_child(mv, curr, &data);
		ft_pipe_parent(&data);
		curr = curr->nc;
		if (curr && ft_cop(curr->n) == 1 && curr->nc)
			curr = curr->nc;
		data.token = ft_get_pipe(data.token);
		data.i++;
	}
	status = ft_wait_children(&data, status);
	free(data.pids);
	return (status);
}
