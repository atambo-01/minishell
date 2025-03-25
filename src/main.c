/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:44:29 by atambo            #+#    #+#             */
/*   Updated: 2025/03/25 21:37:55 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

void	ft_ctrl_d(t_main_vars *mv)
{
	if (mv->line == NULL)
	{
		mv->token = ft_malloc(sizeof(t_token));
		mv->token->s = ft_strdup("exit");
		mv->token->next = NULL;
		ft_exit(mv);
	}
	return ;
}

void	ft_main_nest(t_main_vars *mv)
{
	int	redir;

	mv->cmd = ft_get_cmd(mv->token, mv->env);
	ft_bckp_fd(mv->fd);
	if (mv->cmd != NULL && ft_do_pipe(mv->token) != NULL)
		mv->exit = ft_pipe(mv);
	else if (ft_count_redir(mv->token) > 0)
	{
		redir = ft_get_redir(mv, mv->token, &(mv->fd), &(mv->fd_c));
		if (redir)
			mv->exit = redir;
		else if (mv->cmd != NULL)
			mv->exit = ft_execute(mv->cmd);
	}
	else
		mv->exit = ft_execute(mv->cmd);
}

static void	ft_add_history(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line)
		add_history(line);
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars	mv;

	ft_shell_init(&mv, envp, ac, av);
	while (1)
	{
		ft_signal(1, 0);
		mv.line = readline("@:minshell_prompt > ");
		ft_exit_update(&(mv.exit));
		ft_ctrl_d(&mv);
		if (ft_strlen(mv.line) == 0)
			continue ;
		ft_add_history(mv.line);
		mv.token = ft_token(mv.line, mv.env, mv.exit, &mv);
		if (!mv.token)
			continue ;
		if (ft_exit(&mv) == 1)
			mv.exit = 1;
		else
			ft_main_nest(&mv);
		ft_main_while_free(&mv);
	}
}
