/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:54:39 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 17:20:50 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_path(const char *dir, const char *name)
{
	char	*full_path;
	size_t	len_dir;
	size_t	len_name;

	len_dir = strlen(dir);
	len_name = strlen(name);
	full_path = ft_malloc(len_dir + len_name + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, (char *)dir);
	full_path[len_dir] = '/';
	ft_strcpy(&full_path[len_dir + 1], (char *)name);
	return (full_path);
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
		return (1);
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
		return (r);
	return (-3);
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
			break ;
		if (access(full_path, F_OK | X_OK) == 0)
		{
			cmd->path = full_path;
			return (1);
		}
		free(full_path);
		i++;
	}
	return (-1);
}
