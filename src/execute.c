/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:05:14 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 12:51:41 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_path(const char *dir, const char *name)
{
	char	*full_path;
	size_t	len_dir;
	size_t	len_name;

	len_dir = ft_strlen(dir);
	len_name = ft_strlen(name);
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

	i = 0;
	paths = *p_paths;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->n);
		if (full_path == NULL)
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			cmd->path = full_path;
			return (0);
		}
		free(full_path);
		i++;
	}
	return (1);
}

int	ft_get_path(t_cmd *cmd)
{
	int		r;
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd->n, '/') != NULL)
	{
		cmd->path = ft_strdup(cmd->n); 
		return(0);
	}
	r = 0;
	path_env = getenv("PATH");
	if (!path_env || !cmd || !cmd->n)
		return (1);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (2);
	r = ft_test_paths(cmd, &paths);
	ft_free_pp((void ***)&paths);
	if (r == 0)
		return (r);
	return (3);
}

void	ft_execve_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

void	ft_execve_sigquit(int sig)
{
	(void)sig;
	exit(0);
	g_signal = SIGQUIT;
}

void	ft_execve_sigquit_2(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5);
	g_signal = SIGQUIT;
}

void	ft_builtin_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

int ft_execve_child(t_cmd *cmd)
{
    char **env_p;

    env_p = ft_token_to_envp(cmd->env);
    if (!env_p || !*env_p)
        exit(1);
    if (execve(cmd->path, cmd->params, env_p) == -1)
        exit(2);
    return (0);
}

int ft_execve(t_cmd *cmd)
{
    pid_t   pid;
    int     status;
    struct stat path_stat;

    status = 0;
    if (stat(cmd->path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
    {
		ft_perror("minishell: ", 1);
		ft_perror(cmd->path, 1);
		return (ft_perror(" Is a directory\n", 126));
	}
    pid = fork();
    ft_signal((int []){0, 0, 1, 1, 0, 0});
    if (pid == -1)
        return (ft_perror("fork", -1));
    if (pid == 0)
        ft_execve_child(cmd);
    ft_signal((int []){0, 0, 0, 1, 1, 0});
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        status = 128 + WTERMSIG(status);
    return (status);
}

int	ft_execute(t_cmd *cmd, int p, int r)
{
	pid_t pid;
	int status;

	status = 0;
	if (!cmd)
		return (-1);
	if (cmd->nc && p == 1 && ft_strcmp(cmd->nc->n, "|") == 0)
		return (ft_pipe(cmd->nc));
	//ft_redir(mv.token);
	status = ft_builtin(cmd);
	if (status != 127)
		return (status);
	else if (ft_get_path(cmd) == 0)
		return (ft_execve(cmd));
	else
	{
		ft_putstr_fd(cmd->n, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (127);
	}
	return (status);
}
