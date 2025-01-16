/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:44:20 by eneto             #+#    #+#             */
/*   Updated: 2025/01/16 10:58:23 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute(t_cmd *cmd, int fd)
{
	if (execve(cmd->n, cmd->params, cmd->envp) == -1)
	{
		ft_putstr_fd(cmd->n, fd);
		ft_putstr_fd("Verifique os parametros", fd);
		exit(1);
	}
}