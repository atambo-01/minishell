/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:35:21 by atambo            #+#    #+#             */
/*   Updated: 2025/03/25 21:45:11 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_strjoin_path(const char *dir, const char *name)
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

static int	ft_test_paths(t_cmd *cmd, char ***p_paths)
{
	int		i;
	char	*full_path;
	char	**paths;

	if (cmd->n[0] == '\0')
		return (1);
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
int	ft_get_path_aux(char *path)
{
	if (access(path, F_OK) != 0)
	{
		ft_dprintf(2, "minishell : %s: %s \n", path, strerror(errno));
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_dprintf(2, "minishell : %s: %s \n", path, strerror(errno));
		return (126);
	}

	return (0);
}
int	ft_get_path(t_cmd *cmd)
{
	int		r;
	char	*path_env;
	char	**paths;

	if (ft_strchr(cmd->n, '/') != NULL)
	{
		cmd->path = ft_strdup(cmd->n);
		return (ft_get_path_aux(cmd->path));
	}
	r = 0;
	path_env = ft_getenv(cmd->env, "PATH");
	if (!path_env || !cmd || !cmd->n)
		return (1);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (2);
	r = ft_test_paths(cmd, &paths);
	ft_free_pp((void ***)&paths);
	if (r == 0)
		return (0);
	return (3);
}
