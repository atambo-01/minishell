/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:20 by eneto             #+#    #+#             */
/*   Updated: 2025/01/17 13:55:04 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute(t_cmd *cmd, int fd)
{
	int		i;
	char 	*path;

	while(cmd)
	{
		if (ft_builtin(cmd) == 1);
		{
			cmd->n = ft_get_path(cmd->n, cmd->envp);
			if (execve(cmd->n, cmd->params, cmd->envp) == -1)
			{
				ft_putstr_fd(cmd->n, 2);
				ft_putstr_fd(":", 2);
				ft_putstr_fd(" command not found\n", 2);
			}

		}
		cmd = cmd->next;
	}
}
