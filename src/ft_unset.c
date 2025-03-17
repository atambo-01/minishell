/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:55:21 by eneto             #+#    #+#             */
/*   Updated: 2025/02/27 18:07:32 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd || !cmd->env)
		return (0);
	while (cmd->params[++i])
	{
		if (ft_getenv(cmd->env, cmd->params[i]))
			ft_remove_env_node(&(cmd->env), cmd->params[i]);
	}
	return (0);
}
