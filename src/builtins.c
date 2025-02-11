/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/02/11 11:05:42 by eneto            ###   ########.fr       */
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
void	ft_cd(t_cmd *path)
{
	chdir(path->n);
	if (!path->n)
	{
		ft_putstr_fd("Erro ao abrir pasta/dir", 2);
		return ;
	}
}

// int	ft_builtin(t_cmd *cmd, const int prev_exit)
// {
// 	if (ft_strcmp("echo", cmd->n) == 0)
// 	{
// 		ft_echo(cmd, prev_exit);
// 		return (0);
// 	}
// 	/*
// 	else if (ft_strcmp("cd", cmd->n) == 0) {
// 		ft_cd(cmd);
// 		return (0);
// 	}
// 	else if (ft_strcmp("pwd", cmd->n) == 0) {
// 		ft_pwd(cmd);
// 		return (0);
// 	}
// 	else if (ft_strcmp("export", cmd->n) == 0) {
// 		ft_export(cmd);
// 		return (0);
// 	}
// 	else if (ft_strcmp("unset", cmd->n) == 0) {
// 		ft_unset(cmd);
// 		return (0);
// 	}
// 	else if (ft_strcmp("env", cmd->n) == 0) {
// 		ft_env(cmd);
// 		return (0);
// 	}
// */
// 	return (1);
// }

int	ft_builtin(t_cmd *cmd, char ***ft_envp, const int prev_exit)
{
	if (ft_strcmp(cmd->n, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->n, "echo") == 0)
		ft_echo(cmd, prev_exit);
	else if (ft_strcmp(cmd->n, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->n, "export") == 0)
		ft_export(&(cmd->params[1]), ft_envp);
	// else if (ft_strcmp(cmd->n, "unset") == 0)
	//     ft_unset(cmd->n, ft_envp);
	//else if (ft_strcmp(cmd->n, "exit") == 0)
		//ft_exit(cmd->n, prev_exit);
	return (0);
}