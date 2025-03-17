/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:44:29 by atambo            #+#    #+#             */
/*   Updated: 2025/03/17 18:29:24 by atambo           ###   ########.fr       */
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
	if (mv->cmd != NULL)
	{
		if (ft_get_pipe(mv->token) != NULL)
			ft_pipe(mv, mv->cmd, mv->token);
		else
		{
			if (ft_count_redir(mv->token) > 0)
			{
				redir = ft_get_redir(mv, mv->token, &(mv->fd), &(mv->fd_c));
				if (redir == 0)
					mv->exit = ft_execute(mv->cmd);
				else
					mv->exit = redir;
			}
			else
				mv->exit = ft_execute(mv->cmd);
		}
	}
	else if (ft_count_redir(mv->token) > 0)
		ft_get_redir(mv, mv->token, &(mv->fd), &(mv->fd_c));
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars	mv;

	ft_shell_init(&mv, envp, ac, av);
	while (1)
	{
		ft_signal((int []){1, 1, 0, 0, 0, 0});
		mv.line = readline(COLOR BOLD "攻殻_機動隊 > " RESET);
		ft_ctrl_d(&mv);
		if (ft_strlen(mv.line) == 0)
			continue ;
		mv.exit = ft_exit_update(mv.exit);
		mv.token = ft_token(mv.line, mv.env, mv.exit, &mv);
		if (!mv.token)
			continue ;
		add_history(mv.line);
		if (ft_exit(&mv) == 1)
			mv.exit = 1;
		else
			ft_main_nest(&mv);
		ft_main_while_free(&mv);
	}
}
