/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/01/31 14:36:30 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_cmd *cmd, const int prev_exit)
{
	int	n;

	n = 1;
	if (!cmd || !cmd->n)
		return (1);
	if (ft_strcmp("-n ", cmd->params[0]) == 0)
		n = 2;
	while (cmd->params[n])
	{
		if (ft_strcmp("$?",cmd->params[n]) == 0)
			printf("%d", prev_exit);
		else
			printf("%s", cmd->params[n]);
		n++;
		if (cmd->params[n])
			printf(" ");
	}
	if (n)
		printf("\n");
	return (0);
}

int	ft_builtin(t_cmd *cmd, const int prev_exit)
{
	if (ft_strcmp("echo", cmd->n) == 0)
	{
		ft_echo(cmd, prev_exit);
		return (0);
	}
	/*
	else if (ft_strcmp("cd", cmd->n) == 0) {
		ft_cd(cmd);
		return (0);
	}
	else if (ft_strcmp("pwd", cmd->n) == 0) {
		ft_pwd(cmd);
		return (0);
	}
	else if (ft_strcmp("export", cmd->n) == 0) {
		ft_export(cmd);
		return (0);
	}
	else if (ft_strcmp("unset", cmd->n) == 0) {
		ft_unset(cmd);
		return (0);
	}
	else if (ft_strcmp("env", cmd->n) == 0) {
		ft_env(cmd);
		return (0);
	}
*/
	return (1);
}
