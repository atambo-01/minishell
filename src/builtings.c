/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:31:03 by eneto             #+#    #+#             */
/*   Updated: 2025/01/17 11:26:38 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(t_cmd *cmd)
{
	int	n;

	n = 0;
	if (!cmd || !cmd->n)
		return ;
	if (ft_strncmp("-n ", cmd->params) == 0)
	{
		n = 1;
		cmd->params += 3;
	}
	printf("%s", cmd->params);
	if (n)
		printf("\n");
	return ;
}

void	ft_builtin(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->n) == 0)
		ft_echo();

	else if (ft_strcmp("cd", cmd->n) == 0)
		ft_cd();

	else if (ft_strcmp("pwd", cmd->n) == 0)
		ft_pwd();

	else if (ft_strcmp("export", cmd->n) == 0)
		ft_export();

	else if (ft_strcmp("unset", cmd->n) == 0)
		ft_unset();

	else if (ft_strcmp("env", cmd->n) == 0)
		ft_env();
}
