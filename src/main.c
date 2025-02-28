/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:53:56 by atambo            #+#    #+#             */
/*   Updated: 2025/02/28 03:22:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_signal;

int	ft_token_size(t_token *head)
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

void	ft_token_ls(t_token *token)
{
	int i;

	i = 0;
	if (!token || !token->s)
		return ;
	i = ft_token_size(token);
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
			printf("cmd_ls = %s\t:", cmd->n);
			if (cmd->params)
			{
				i = 0;
				while (cmd->params[i])
				{
					printf(" {%s} ", cmd->params[i]);
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

void	ft_free_token(t_token **p_token)
{
	t_token *token;
	t_token *next;

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
	token = NULL;
}

static void	ft_minishell_init(t_main_vars *mv, char **envp)
{
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
	int		n;
	t_cmd	*cmd;
	t_cmd	*next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	while (cmd)
	{
		next = cmd->nc;
		if (cmd->params)
		{
			n = 0;
			while(cmd->params[n])
			{
				free(cmd->params[n]);
				n++;
			}
			free(cmd->params);
		}
//		ft_free_pp((void ***)&(cmd->params));
//		ft_free_pp((void ***)&(cmd->redir));
		free(cmd->n);

		free(cmd->path);

		cmd->env = NULL;
		free(cmd);
		cmd = next;
	}
}

void	ft_main_while_free(t_main_vars *mv)
{
	ft_restore_fd(mv->fd);	
	if (mv->line)
		free(mv->line);
	if (mv->token)
		ft_free_token(&(mv->token));
	if (mv->cmd)
		ft_free_cmd(&(mv->cmd));
}

int		ft_exit_update(int i)
{
	int ret;

	ret = i;
	if (g_signal == SIGINT)
		ret = 130;
	else if (g_signal == SIGQUIT)
		ret = 131;
	g_signal = 0;
	return(ret);
}

void	ft_minishell_exit(t_main_vars *mv)
{

	if (!mv)
		return ;
	ft_free_env(&(mv->env));
	free(mv->line);
	rl_clear_history();
}
int	ft_is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return(0);
	while(ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return(1);
}

int    ft_exit(t_main_vars *mv)
{
    int		num;
	char	*temp;	
	
	temp = ft_get_subtoken(mv->token->s);
	if (ft_strcmp(temp, "exit") != 0)
	{
		free(temp);
		return(0);
	}
	free(temp);
	
	ft_main_while_free(mv);

	printf("exit\n");
	if (!mv->token->next)
		exit(0)	;	
	else if (mv->token->next)
	{
		if (ft_is_numeric(mv->token->next->s) == 0)
			exit(ft_perror("minishell: exit: numeric argument needed\n", 2));
		if (mv->token->next->next)
			return(ft_perror("exit: to many arguments\n", 1));
		exit(ft_atoi(mv->token->next->s));
	}
}


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_main_vars	mv;

	ft_minishell_init(&mv, envp);
//	ft_token_env(mv.env);
	while (1)
	{
		ft_signal((int []){1, 1, 0, 0, 0, 0});
		mv.line = readline(COLOR BOLD "攻殻機動隊 > " RESET);
	//	sleep(5);
		if (ft_strlen(mv.line) > 0)
		{
			mv.exit = ft_exit_update(mv.exit);
			add_history(mv.line);
			mv.token = ft_token(mv.line, mv.env, mv.exit);
			if (ft_exit(&mv) != 0)
				mv.exit = 1;
			else if (mv.token != NULL)
			{

			//	ft_token_ls(mv.token);
				mv.cmd = ft_get_cmd(mv.token, mv.env);
				ft_bckp_fd(mv.fd);
				if (mv.cmd != NULL)
				{
				//	ft_cmd_ls(mv.cmd);
					if (ft_get_pipe(mv.token) != NULL)
						ft_pipe(&mv, mv.cmd, mv.token);
					else 
					{
						if (ft_count_redir(mv.token) > 0)
						{	
							int redir = ft_get_redir(mv.token, &(mv.fd), &(mv.fd_c));
							if (redir == 0)
								mv.exit = ft_execute(mv.cmd);
							else
								mv.exit = redir;
						}
						else
							mv.exit = ft_execute(mv.cmd);
					}
				}
				else if (ft_count_redir(mv.token) > 0)
					ft_get_redir(mv.token, &(mv.fd), &(mv.fd_c));
			}
			ft_main_while_free(&mv);
		}
	}
}
