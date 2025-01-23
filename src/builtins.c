/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/01/20 12:58:44 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	n;

	n = 0;
	if (!cmd || !cmd->n)
		return ;
	if (ft_strcmp("-n ", cmd->params[0]) == 0)
		n = 1;
	while(cmd->params[n])
	{
		printf("%s", cmd->params[n]);
		n++;
		if (cmd->params[n])
			printf(" ");
	}
	if (n)
		printf("\n");
	return ;
}

int ft_builtin(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->n) == 0)
	{
        ft_echo(cmd);
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
    return (1); // Command is not a built-in
}

