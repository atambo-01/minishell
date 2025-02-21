/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:58:53 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 17:58:53 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_exit = 1;

void	ft_cmd_ls(t_cmd *cmd)
{
	if (!cmd)
		return ;
	int i = 0;
	while (cmd)
	{
		if (cmd && cmd->n)
		{
			printf("cmd_ls = %s\t: ", cmd->n);
			if (cmd->params)
			{
				i = 0;
				while (cmd->params[i])
				{
					printf("%s ", cmd->params[i]);
					i++;
				}
			}
			if (cmd->redir)
			{
				i = 0;
				while (cmd->redir[i])
				{
					printf("%s ", cmd->redir[i]);
					i++;
				}
			}
			printf("\n");
		}
		cmd = cmd->nc;
		i++;
		if (cmd && cmd->n)
			printf("\n");
	}
	return ;
}

static void	ft_minishell_init(t_main_vars *mv, char **envp)
{
	g_exit = 0;
	mv->token = NULL;
	mv->cmd = NULL;
	mv->line = NULL;
	mv->exit = -1;
	mv->env = ft_envp_to_list(envp);
}

static void  ft_minishell_exit(t_main_vars **p_mv)
{
	t_main_vars *mv;

	if (!p_mv || !*p_mv)
		return ;
	mv = *p_mv;
	if (mv->cmd)
		ft_free_cmd(&(mv->cmd));
	if (mv->token)
		ft_free_token(&(mv->token));
	if (mv->line)
		ft_free_p((void **)&(mv->line));
	if (mv->env)
		ft_free_env(&(mv->env));
	ft_free_p((void **)&(*p_mv));
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars mv;

	(void)ac;
	(void)av;
	ft_minishell_init(&mv, envp);
	while (1)
	{
		sig_call();
		mv.line = readline("minishell_prompt > ");
		ctrl_d(&mv);
		if (ft_strlen(mv.line) > 0)
		{
			//	printf("line =_%s\n", mv.line);
			add_history(mv.line);
			if (ft_strcmp(mv.line, "exit") == 0)
				break ;
			else if ((mv.token = ft_get_token(mv.line, mv.env,
						mv.exit)) != NULL)
			{
				ft_token_ls(mv.token);
				if ((mv.cmd = get_cmd(mv.token, mv.env)) != NULL)
				{
					ft_cmd_ls(mv.cmd);
					mv.exit = ft_execute(mv.cmd, 1, 1);
					// ft_free_cmd(&(mv.cmd));
				}
				//		ft_free_token(&(mv.token));
			}
		}
		//	free(mv.line);
	}
	rl_clear_history();
	ft_free_p((void **)&(mv.line));
}
