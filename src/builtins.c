/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/03/07 16:57:11 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo_flags(char *str, char *flags)
{
	ft_memset(flags, 0, 53);
	while (*str)
	{
		if (*str == 'n')
			flags['n' - 'a'] = 1;
		else
		{
			ft_memset(flags, 0, 53);
			return (0);
		}
		str++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		n;
	char	flags[53];

	if (!cmd)
		return (1);
	n = 1;
	ft_memset(flags, 0, 53);
	if (!cmd->params[1])
	{
		printf("\n");
		return (0);
	}
	if (cmd->params[1][0] == '-' && cmd->params[1][1])
		n += ft_echo_flags(&(cmd->params[1][1]), flags);
	while (cmd->params[n])
	{
		printf("%s", cmd->params[n]);
		n++;
		if (cmd->params[n])
			printf(" ");
	}
	if (flags['n' - 'a'] == 0)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX);
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	ft_free_p((void **)&buff);
	return (0);
}

int ft_cd_error(int error_type, char *path)
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
    struct stat path_stat;

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


int	ft_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	if (!cmd->n)
		return (1);
	ft_signal((int[]){0, 0, 0, 0, 0, 1});
	if (ft_strcmp(cmd->n, "cd") == 0)
		return (ft_cd(cmd));
	else if (ft_strcmp(cmd->n, "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->n, "env") == 0)
		return (ft_env(cmd));
	else if (ft_strcmp(cmd->n, "unset") == 0)
		return (ft_unset(cmd));
	else if (ft_strcmp(cmd->n, "export") == 0)
		return (ft_export(cmd->params, &(cmd->env)));
	else if (ft_strcmp(cmd->n, "set_exit") == 0)
		return (ft_atoi((cmd->params[1])));
	return (127);
}
