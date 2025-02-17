/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/02/15 18:58:26 by atambo           ###   ########.fr       */
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

	if (ft_strchr(cmd->n, '/') != NULL)
	{
		cmd->path = realpath(cmd->n, NULL);
		return(1);
	}
	r = 0;
	path_env = getenv("PATH");
	if (!path_env || !cmd || !cmd->n)
		return (-1);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (-2);
	r = ft_test_paths(cmd, &paths);
	ft_free_pp((void ***)&paths);
	if (r == 1)
		return(r);
	return (-3);
}

int	ft_execve(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**env_p;
	
	status = 0;
	env_p = NULL;
	pid = fork();
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
	if (status != 0)
		return(ft_perror("error: ft_execve.\n", status));
	return(status);
}

int    ft_redir_out(t_cmd *cmd, int i, int prev_exit)
{
    int fd[3];
	int	status;

	printf("redir_out\n");
    if (!cmd->redir[i + 1])
        return(ft_perror("Syntax error: missing file\n", -1));
    fd[0] = open(cmd->redir[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd[0] == -1)
        ft_perror("open", -1);
    fd[1] = dup(STDOUT_FILENO);
    if (fd[1] == -1)
    {
		close(fd[0]);
        return(ft_perror("dup (saving stdout)", -1));
    }
    if (dup2(fd[0], STDOUT_FILENO) == -1)
    {
        close(fd[0]);
        close(fd[1]);
		return(ft_perror("dup2 (redirecting stdout)", -1));
    }
	fd[2] = ft_execute(cmd, 0, prev_exit, 0);
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        close(fd[1]);
		return(ft_perror("dup2 (restoring stdout)", -1));
    }
    close(fd[1]);
	return (fd[2]);
}


int	ft_redirect(t_cmd *cmd, int prev_exit)
{
	int	i;

	i = 0;
	if (!cmd->redir)
		return (1);
	while(cmd->redir[i])
	{
		printf("redir\n");
		if (ft_cop(cmd->redir[i]) == 2)
			return(ft_redir_out(cmd, i, prev_exit));
/*		else if (ft_ctrl_operator(cmd->params[i]) == 3)
			ft_redir_in();
		else if (ft_ctrl_operator(cmd->params[i]) == 4)
			ft_redir_append();
		else if (ft_ctrl_operator(cmd->params[i]) == 5)
			ft_readoc();
*/		i++;
	}
	return(42);
}


int ft_execute(t_cmd *cmd, int p, const int prev_exit, int r)
{
	pid_t   pid;
	int		status;
	
	status = 0;
	if (!cmd)
		return (-1);
	if(cmd->nc && p == 1 && ft_strcmp(cmd->nc->n, "|") == 0)
		return(ft_pipe(cmd->nc, prev_exit));
	if (r && cmd->redir && (status = ft_redirect(cmd, prev_exit) == 0))
		return(status);
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
	return (status);
}
