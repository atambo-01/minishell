/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:09:11 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 22:57:01 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*temp;

	temp = NULL;
	if (!cmd)
		exit (1);
	if (cmd->params[1])
		exit (ft_perror("env: too many arguments\n", 2));
	temp = cmd->env;
	while (temp)
	{
		printf("%s", temp->name);
		if (temp->value != NULL)
			printf("=%s", temp->value);
		printf("\n");
		temp = temp->next;
	}
	exit(0);
}
