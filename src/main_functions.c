/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:49:13 by atambo            #+#    #+#             */
/*   Updated: 2025/03/23 13:13:43 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_update(int *i)
{
	int	ret;

	ret = *i;
	if (g_signal == SIGINT)
		ret = 130;
	else if (g_signal == SIGQUIT)
		ret = 131;
	g_signal = 0;
	*i = ret;
}

void	ft_free_token(t_token **p_token)
{
	t_token	*token;
	t_token	*next;

	if (!p_token || !*p_token || !(*p_token)->s)
		return ;
	token = *p_token;
	while (token)
	{
		next = token->next;
		free(token->s);
		token->s = NULL;
		free(token);
		token = next;
	}
	*p_token = NULL;
}

void	ft_shell_init(t_main_vars *mv, char **envp, int ac, char **av)
{
	(void)ac;
	(void)av;
	g_signal = 0;
	mv->token = NULL;
	mv->cmd = NULL;
	mv->line = NULL;
	mv->fd = NULL;
	mv->exit = 0;
	mv->env = ft_envp_to_list(envp);
	mv->fd = ft_malloc(sizeof(int) * (10000));
	ft_bckp_fd(mv->fd);
}

void	ft_free_cmd(t_cmd **p_cmd)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	next = NULL;
	while (cmd)
	{
		if (cmd->nc)
			next = cmd->nc;
		else
			next = NULL;
		cmd->env = NULL;
		if (cmd->params)
			ft_free_pp((void ***)&(cmd->params));
		if (cmd->path)
			ft_free_p((void *)&(cmd->path));
		if (cmd->n)
			ft_free_p((void *)&(cmd->n));
		if (cmd)
			ft_free_p((void *)&(cmd));
		cmd = next;
	}
}

void	ft_main_while_free(t_main_vars *mv)
{
	ft_restore_fd(mv->fd, 1, 1);
	if (mv->line)
	{
		free(mv->line);
		mv->line = NULL;
	}
	if (mv->token)
	{
		ft_free_token(&(mv->token));
		mv->token = NULL;
	}
	if (mv->cmd)
	{
		ft_free_cmd(&(mv->cmd));
		mv->cmd = NULL;
	}
}
