/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/02/18 00:19:40 by atambo           ###   ########.fr       */
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

int    ft_redir_out(t_cmd *cmd, int i, int fd[], int *i_fd)
{
    fd[*i_fd] = open(cmd->redir[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd[*i_fd] == -1)
        return (ft_perror("minshell: Permission denied\n", -1));
    if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}

int    ft_redir_in(t_cmd *cmd, int i, int fd[], int *i_fd)
{
    fd[*i_fd] = open(cmd->redir[i + 1],O_RDONLY);
    if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", -1));
    if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdin\n", -1));
	(*i_fd)++;
	return (0);
}

int    ft_redir_append(t_cmd *cmd, int i, int fd[], int *i_fd)
{
    fd[*i_fd] = open(cmd->redir[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd[*i_fd] == -1)
       	return (ft_perror("minshell: Permission denied\n", -1));
    if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", -1));
	(*i_fd)++;
	return (0);
}

int	count_redir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while(cmd->redir[i])
		i++;
	return(i);
}

int	mod_fd(t_cmd *cmd, int i, int fd[], int *i_fd)
{
	int cop;

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

int	bckp_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		return (1);
	}
	return (0);
}

void	close_fd(int fd[], int i_fd)
{
	int j;

	j = 3;
	while(j < i_fd)
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


int	ft_redirect(t_cmd *cmd)
{
	int	*fd;
	int r;
	int	i;
	int	i_fd;
	int status;
	
	if (!cmd->redir)
		return (1);
	fd = ft_malloc(sizeof(int) * (count_redir(cmd) + 1));
	if (bckp_fd(fd) != 0)
		return (ft_perror("error: saving std fds\n", -1));
	i = 0;
	i_fd = 3;
	while(cmd->redir[i])
	{
		r = mod_fd(cmd, i, fd, &i_fd);
		if (r == -1)
			return (-1);
		i++;
	}
	status = ft_execute(cmd, 0, 0);
	close_fd(fd, i_fd);
	return (status);
}


int ft_execute(t_cmd *cmd, int p, int r)
{
	pid_t   pid;
	int		status;
	
	status = 0;
	if (!cmd)
		return (-1);
	if(cmd->nc && p == 1 && ft_strcmp(cmd->nc->n, "|") == 0)
		return(ft_pipe(cmd->nc));
	if (r && cmd->redir)
		return (ft_redirect(cmd));
	status = ft_builtin(cmd);
	if (status != 127)
		return (status);
	else if	(ft_get_path(cmd) == 1)
		return (ft_execve(cmd));
	else 
	{
			ft_putstr_fd(cmd->n, 1);
			ft_putstr_fd(": command not found\n", 1);
			return (127);
	}
	return (status);
}


