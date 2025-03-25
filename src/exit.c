/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:04:30 by atambo            #+#    #+#             */
/*   Updated: 2025/03/23 13:11:40 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_free(t_main_vars *mv)
{
	if (!mv)
		return ;
	ft_restore_fd(mv->fd, 1, 1);
	rl_clear_history();
	free(mv->line);
	ft_free_token(&(mv->token));
	free(mv->fd);
	mv->fd = NULL;
}

int	ft_exit(t_main_vars *mv)
{
	int	num;
	int	status;

	status = 0;
	num = mv->exit;
	if (ft_strcmp(mv->token->s, "exit") != 0)
		return (0);
	printf("exit\n");
	if (mv->token->next)
	{
		if (mv->token->next->next)
			status = 1;
		num = ft_exit_atoi(mv->token->next->s);
		if (num == -1)
			num = (ft_perror("minishell: exit: need a numeric argument\n", 2));
		else if (status == 1)
			return (ft_perror("minishell: exit: to many arguments\n", status));
	}
	ft_free_env(mv->env);
	ft_exit_free(mv);
	exit(num);
}
