/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:51:13 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo_flags(char *str, char *flags)
{
	int		i;
	char	curr_flags[53];

	ft_memset(&curr_flags, 0, 53);
	if (!str || *str != '-' || !str[1])
		return (0);
	str++;
	while (*str)
	{
		if (*str == 'n')
			curr_flags['n' - 'a'] = 1;
		else
			return (0);
		str++;
	}
	i = 0;
	while (i < 53)
	{
		flags[i] = curr_flags[i];
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		n;
	char	flags[53];

	ft_memset(&flags, 0, 53);
	if (!cmd)
		return (1);
	n = 1;
	while (cmd->params[n])
	{
		if (ft_echo_flags(cmd->params[n], flags))
			n++;
		else if (cmd->params[n])
		{
			printf("%s", cmd->params[n]);
			n++;
			if (cmd->params[n])
				printf(" ");
		}
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

int	ft_builtin(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	if (!cmd->n)
		return (1);
	ft_signal(3, 0);
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
	{
		if (cmd->params[1])
			return (ft_atoi((cmd->params[1])));
		return (0);
	}
	return (127);
}
