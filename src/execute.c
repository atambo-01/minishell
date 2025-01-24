#include "../inc/minishell.h"

char *ft_strjoin_path(const char *dir, const char *name)
{
	char *full_path;
	size_t len_dir = strlen(dir);
	size_t len_name = strlen(name);

	full_path = ft_malloc(len_dir + len_name + 2); // +1 for '/' and +1 for '\0'
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, (char *)dir);
	full_path[len_dir] = '/';
	ft_strcpy(&full_path[len_dir + 1], (char *)name);
	return (full_path);
}

int	ft_get_path(t_cmd *cmd)
{
	char *path_env = getenv("PATH");
	char **paths;
	char *full_path;
	int i;

	if (!path_env || !cmd || !cmd->n)
		return (-1);

	paths = ft_split(path_env, ':'); // Split PATH into directories
	if (!paths)
		return (-2);

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->n);
		if (!full_path)
			break;
		if (access(full_path, F_OK | X_OK) == 0) // Check if command is executable
		{
			ft_free_pp((void ***)&paths); // Free the split PATH
			ft_free_p((void **)&cmd->n);
			cmd->path = full_path;
			return(1);
		}
		free(full_path);
		i++;
	}
	ft_free_pp((void ***)&paths); // Free the split PATH
	return (-3);		// Command not found
}

int ft_execute(t_cmd *cmd, int p)
{
	pid_t   pid;
	int	 status;
	
	if (!cmd)
		return (0);
	if(cmd->nc && cmd->nc->n)
	{
		if (p == 0 && ft_strcmp(cmd->nc->n, "|") == 0)
			ft_pipe(cmd->nc);
	}
	while (cmd && cmd->n)
	{
		if (ft_builtin(cmd) == 0)
		{
			cmd = cmd->nc;
			continue;
		}
		else if ((pid = fork()) == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{	
			if (ft_get_path(cmd))
			{
				printf("execve\n");
				printf("cmd->path = %s\n", cmd->path);
				ft_putlines(cmd->params);
				ft_putstr("\n");
				if (execve(cmd->path, cmd->params, cmd->ft_envp) == -1)
				{
					ft_putstr_fd(cmd->n, 1);
					ft_putstr_fd(": ", 1);
					ft_putstr_fd("command not found\n", 1);
					exit(127);
				}
			}
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0); // Wait for the child process
			if (WIFEXITED(status))
				g_exit = WEXITSTATUS(status); // Capture the child's exit status
			else if (WIFSIGNALED(status))
				g_exit = 128 + WTERMSIG(status); // Signal termination status
		}
		cmd = cmd->nc; // Move to the next command
	}
	return (g_exit);
}
