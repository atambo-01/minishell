/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:09:11 by eneto             #+#    #+#             */
/*   Updated: 2025/03/01 02:35:22 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*temp;
	while(!g_signal)
	{
		temp = NULL;
		if (!cmd)
			return (1);
		if (cmd->params[1])
			return (ft_perror("env: too many arguments\n", 2));
		temp = cmd->env;
		while (temp)
		{
			if (g_signal == SIGINT || g_signal == SIGQUIT)
				return (0);
			if (temp->value != NULL)
			{
				printf("%s", temp->name);
				printf("=%s", temp->value);
				printf("\n");
			}
			temp = temp->next;
		}
		return (0);
	}
	return (0);
}
