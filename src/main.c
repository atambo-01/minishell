/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/18 11:30:17 by atambo            #+#    #+#             */
/*   Updated: 2025/02/16 20:57:22 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_exit = 1;

int	ft_list_size(t_list *head)
{
	int i;

	i = 0;
	if (!head)
		return (0);
	while (head->next)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	ft_token_ls(t_list *token)
{
	int i;

	i = 0;
	if (!token || !token->s)
		return ;
	i = ft_list_size(token);
	while (i-- > -1)
	{
		printf("{%s}", token->s);
		printf(" ");
		token = token->next;
	}
	printf("\n");
	return ;
}

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
				while(cmd->redir[i])
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

void	ft_free_token(t_list **p_token)
{
	t_list *token;
	t_list *next;

	if (!p_token || !*p_token || !(*p_token)->s)
		return ;
	token = *p_token;
	while (token)
	{
		next = token->next;
		free(token->s);
		token->s = NULL;
		free(token);
		token = NULL;
		token = next;
	}
}

static void	ft_minishell_init(t_main_vars *mv, char **envp)
{
	g_exit = 0;
	mv->token = NULL;
	mv->cmd = NULL;
	mv->line = NULL;
	mv->exit = -1;
	mv->env = ft_envp_to_list(envp);
	ft_add_env_node(mv->env, "SHELL=minishell");
	ft_add_env_node(mv->env, "HOME=");
}

static void	ft_minishell_exit(t_main_vars **p_mv)
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

void	ft_free_cmd(t_cmd **p_cmd)
{
	int n;
	t_cmd *cmd;
	t_cmd *next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	while (cmd)
	{
		next = cmd->nc;
		n = 0;
		while(cmd->params[n] != NULL)
		{
			free(cmd->params[n]);
			n++;
		}
		ft_free_pp((void ***)&(cmd->params));
		cmd->params = NULL;
		free(cmd->n);
		free(cmd->path);
		cmd->env = NULL;
		free(cmd);
		cmd = next;
	}
	*p_cmd = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars mv;

	ft_minishell_init(&mv, envp);
	signal(SIGINT, ctrl_c);
	while (1)
	{
	 	mv.line = readline("minishell_prompt > ");
	 	if (ft_strlen(mv.line) > 0)
	 	{
	 	//	printf("line =_%s\n", mv.line);
	 		add_history(mv.line);
	 		if (ft_strcmp(mv.line, "exit") == 0)
				break ;
	 		else if ((mv.token = ft_get_token(mv.line, mv.env, mv.exit)) != NULL)
	 		{
	 			ft_token_ls(mv.token);
				if ((mv.cmd = get_cmd(mv.token, mv.env)) != NULL);
	 			{
	 				ft_cmd_ls(mv.cmd);
	 	//			mv.exit = ft_execute(mv.cmd, 1, mv.exit, 1);
	 				//ft_free_cmd(&(mv.cmd));
	 			}
		//		ft_free_token(&(mv.token));
	 		}
	 	}
	 //	free(mv.line);
	 }
	 rl_clear_history();
	 ft_free_p((void **)&(mv.line));
}
