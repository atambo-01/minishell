/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/02/07 12:24:04 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_strjoin_path(const char *dir, const char *name)
{
	char *full_path;
	size_t len_dir = strlen(dir);
	size_t len_name = strlen(name);

	full_path = ft_malloc(len_dir + len_name + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, (char *)dir);
	full_path[len_dir] = '/';
	ft_strcpy(&full_path[len_dir + 1], (char *)name);
	return (full_path);
}

int	ft_test_paths(t_cmd *cmd, char ***p_paths)
{
	int		i;
	char	*full_path;
	char	**paths;

	if (!p_paths || !*p_paths)
		return (0);
	i = 0;
	paths = *p_paths;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->n);
		if (full_path == NULL)
			break;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			cmd->path = full_path;
			return(1);
		}
		free(full_path);
		i++;
	}
	return(-1);
}

int	ft_get_path(t_cmd *cmd)
{
	int		r;
	char	*path_env;
	char	**paths;
	char	*full_path;

	r = 0;
	path_env = getenv("PATH");
	if (!path_env || !cmd || !cmd->n)
		return (-1);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (-2);
	r = ft_test_paths(cmd, &paths);
	ft_free_pp((void ***)&paths); // Free the split PATH
	if (r == 1)
		return(r);
	return (-3);		// Command not found
}

int	ft_execve(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->params, cmd->ft_envp) == -1)
		{
			perror("execve");
			_exit(2);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	return(status);
}

/*
void	ft_redirect(t_cmd *cmd)
{
	0 - expand relative and abs paths in expand
			by this step ur redirs and expanded paths should be inside
			the cmd->params matrix
	1 - check if there is redirect
	1.5 - if in the redir in if out then redir out
	2 - check file and open file
	3 - read or write file
}
*/

int ft_execute(t_cmd *cmd, int p, const int prev_exit)
{
	pid_t   pid;
	int		status;
	
	status = 0;
	if (!cmd)
		return (-1);
	if(cmd->nc && p == 1 && ft_strcmp(cmd->nc->n, "|") == 0)
	{
		status = (ft_pipe(cmd->nc, prev_exit));
		cmd = cmd->nc->nc;
	}
//	ft_redirect(cmd);
	else if (cmd->n)
	{
		if ((status = ft_builtin(cmd, prev_exit)) == 0)
			return (status);
		else if	(ft_get_path(cmd) == 1)
			status = ft_execve(cmd);
		else 
		{
			ft_putstr_fd(cmd->n, 1);
			ft_putstr_fd(": command not found\n", 1);
			return (127);
		}
	}
	return (status);
}
