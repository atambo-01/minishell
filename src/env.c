/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:09:11 by eneto             #+#    #+#             */
/*   Updated: 2025/02/22 12:58:32 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*temp;

	temp = NULL;
	if (!cmd)
		return (1);
	if (cmd->params[1])
	{
		ft_perror("cd: ", 1);
		ft_perror(cmd->params[1], 1);
		ft_perror(": No such file or directory\n", 1);
	}
	temp = cmd->env;
	while (temp)
	{
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

int ft_exit(char **args)
{
	(void)args;
	//ft_minishell_exit(args);
	free(&args);
	exit(0);
	return (0);
}
