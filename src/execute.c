/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/02/21 17:55:54 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execve(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**env_p;

	status = 0;
	env_p = NULL;
	pid = fork();
	signal(SIGQUIT, ft_execve_sigquit);
	if (pid == -1)
		return (ft_perror("fork", -1));
	if (pid == 0)
	{
		env_p = ft_list_to_envp(cmd->env);
		if (!env_p || !*env_p)
			exit(1);
		if (execve(cmd->path, cmd->params, env_p) == -1)
			exit(2);
	}
	else
	{
		signal(SIGQUIT, ft_execve_sigquit_2);
		signal(SIGINT, ft_execve_sigint);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		//	signal(SIGINT, ctrl_c);
	}
	return (status);
}

int	mod_fd(t_cmd *cmd, int i, int fd[], int *i_fd)
{
	int	cop;

	cop = ft_cop(cmd->redir[i]);
	if (cop == 2)
		return (ft_redir_out(cmd, i, fd, i_fd));
	else if (cop == 3)
		return (ft_redir_in(cmd, i, fd, i_fd));
	else if (cop == 4)
	{
		return (ft_redir_append(cmd, i, fd, i_fd));
	}
	/*
	else if (ft_cop(cmd->params[i]) == 5)
	{
		return (ft_heredoc(cmd, i, fd, i_fd));
	}
*/
	return (0);
}

void	close_fd(int fd[], int i_fd)
{
	int	j;

	j = 3;
	while (j < i_fd)
	{
		close(fd[j]);
		j++;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[1]);
	close(fd[2]);
}

int	ft_execute(t_cmd *cmd, int p, int r)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!cmd)
		return (-1);
	if (cmd->nc && p == 1 && ft_strcmp(cmd->nc->n, "|") == 0)
		return (ft_pipe(cmd->nc));
	if (r && cmd->redir)
		return (ft_redirect(cmd));
	status = ft_builtin(cmd);
	if (status != 127)
		return (status);
	else if (ft_get_path(cmd) == 1)
		return (ft_execve(cmd));
	else
	{
		ft_putstr_fd(cmd->n, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (127);
	}
	return (status);
}
