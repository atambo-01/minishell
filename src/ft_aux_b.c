/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:38:04 by eneto             #+#    #+#             */
/*   Updated: 2025/03/21 14:44:35 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strstr(char *str, char *str_find)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == str_find[j])
		{
			if (!str_find[j + 1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_cd_error(int error_type, char *path)
{
	ft_perror("minishell :cd: ", 1);
	ft_perror(path, 1);
	if (error_type == 1)
		ft_perror(": No such file or directory\n", 1);
	else if (error_type == 2)
		ft_perror(": Not a directory\n", 1);
	else if (error_type == 3)
		ft_perror(": Permission denied\n", 1);
	else if (error_type == 4)
		ft_perror(": Failed to change directory\n", 1);
	return (1);
}

int	ft_cd(t_cmd *cmd)
{
	struct stat			path_stat;

	if (!cmd->params[1])
		return (0);
	if (cmd->params[2])
		return (ft_perror("minishell: cd: too many arguments\n", 2));
	if (access(cmd->params[1], F_OK) != 0)
		return (ft_cd_error(1, cmd->params[1]));
	stat(cmd->params[1], &path_stat);
	if (!S_ISDIR(path_stat.st_mode))
		return (ft_cd_error(2, cmd->params[1]));
	if (access(cmd->params[1], X_OK) != 0)
		return (ft_cd_error(3, cmd->params[1]));
	if (chdir(cmd->params[1]) == -1)
		return (ft_cd_error(4, cmd->params[1]));
	return (0);
}
