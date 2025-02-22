/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/02/22 07:53:03 by atambo           ###   ########.fr       */
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

int	ft_cd(t_cmd *cmd)
{
	t_env	*home;

	if (cmd->params[2])
		return (ft_perror("cd: too many arguments\n", 1));
	if (!cmd->params[1])
	{
		home = ft_get_env(cmd->env, "HOME");
		if (!home || !home->value)
			return (ft_perror("minishell: cd: HOME not set.", 1));
		chdir(home->value);
		return (0);
	}
	chdir(cmd->params[1]);
	return (0);
}

int	ft_builtin(t_cmd *cmd)
{
	ft_signal((int []){0, 0, 0, 1, 1});
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
	/*else if (ft_strcmp(cmd->n, "exit") == 0)
		return (ft_exit(cmd->n, prev_exit));
*/
	return (127);
}
