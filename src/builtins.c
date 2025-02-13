/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/02/12 23:16:07 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo_flags(char *str, char *flags)
{
	ft_memset(flags, 0, 53);
	while(*str)
	{
		if (*str == 'n')
			flags['n' - 'a'] = 1;
		else
		{
			ft_memset(flags, 0, 53);
			return(0);
		}
		str++;
	}
	return(1);
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
		return(0);
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

int	ft_cd(t_cmd *cmd)
{
	t_env *home;

	home = NULL;
	if (cmd->params[1])
		return(chdir(cmd->params[1]));
	else
	{
		home = ft_get_env(cmd->env, "HOME");
		if (!home)
			return(ft_perror("minishell: cd: HOME not set.", -1));
		return(chdir(home->value));
	}	
}

int	ft_builtin(t_cmd *cmd, const int prev_exit)
{
	if		(ft_strcmp(cmd->n, "cd") == 0)
		return (ft_cd(cmd));
	else if (ft_strcmp(cmd->n, "echo") == 0)
		return (ft_echo(cmd));
/*	else if (ft_strcmp(cmd->n, "env") == 0)
		return (ft_env(cmd));
	else if (ft_strcmp(cmd->n, "unset") == 0)
	    return (ft_unset(cmd->n, ft_envp));
	else if (ft_strcmp(cmd->n, "exit") == 0)
		return (ft_exit(cmd->n, prev_exit));
*/	return (1);
	
}
