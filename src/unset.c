/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:10:28 by eneto             #+#    #+#             */
/*   Updated: 2025/02/15 12:21:39 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_unset(t_cmd *cmd, t_env **envp)
{
    int i;

    i = 1;
    if (!cmd)
        return (1);
    while (cmd->params[i])
    {
        ft_remove_env_node(envp, cmd->params[i]);
        i++;
    }
    return (0);
}