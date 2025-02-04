/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/02/03 11:29:43 by eneto            ###   ########.fr       */
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
	while (cmd->params[n])
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
void	ft_cd(t_cmd *path)
{
	chdir(path->n);
	if (!path->n)
	{
		ft_putstr_fd("Erro ao abrir pasta/dir", 2);
		return ;
	}
}

int	ft_builtin(t_cmd *cmd, char ***ft_envp)
{
	// Note que quando há pipes tudo acontece em um filho
	if (ft_strcmp("echo", cmd->n) == 0)
	{
		ft_echo(cmd);
		return (0);
	}
	else if (ft_strcmp("cd", cmd->n) == 0)
	{
		ft_cd(cmd);
		return (0);
	}
	else if (ft_strcmp("pwd", cmd->n) == 0)
	{
		ft_pwd();
		return (0);
	}
	else if (ft_strcmp("export", cmd->n) == 0)
	{
		ft_export(cmd->params, ft_envp);
		return (0);
	}
	/*else if (ft_strcmp("unset", cmd->n) == 0)
	{
		ft_unset(cmd);
		return (0);
	}*/
	else if (ft_strcmp("env", cmd->n) == 0)
	{
		ft_env(cmd);
		return (0);
	}
	return (1);
}
