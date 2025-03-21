/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 00:17:11 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execve_child(t_cmd *cmd)
{
	char	**env_p;

	env_p = ft_token_to_envp(cmd->env);
	if (!env_p || !*env_p)
		exit(1);
	if (execve(cmd->path, cmd->params, env_p) == -1)
		exit(2);
	return (0);
}

int	ft_execve(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	ft_signal(2, 2);
	if (pid == -1)
		return (ft_perror("fork", -1));
	if (pid == 0)
		ft_execve_child(cmd);
	ft_signal(0, 0);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	if (status == 2)
	{
		ft_perror("minshell: ", 0);
		ft_perror(cmd->n, 0);
		return (ft_perror(" : Permission denied\n", 126));
	}
	return (status);
}

int	ft_execute(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (!cmd)
		return (-1);
	status = ft_builtin(cmd);
	if (status != 127)
		return (status);
	status = ft_get_path(cmd);
	if (status == 0)
		return (ft_execve(cmd));
	else if (1 <= status && status <= 3)
	{
		ft_perror(cmd->n, 1);
		status = ft_perror(": command not found\n", 127);
	}
	return (status);
}
