/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:30:17 by atambo            #+#    #+#             */
/*   Updated: 2025/01/26 00:54:45 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit = 0;

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
		printf("%s", token->s);
		printf("->");
		token = token->next;
	}
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
				while(cmd->params[i])
				{
					printf("%s ", cmd->params[i]);
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
	printf("\n");
	return ;
}

void	ft_free_token(t_list **p_token)
{
	t_list	*token;
	t_list	*next;

	if (!p_token || !*p_token || !(*p_token)->s)
		return;
	token = *p_token;
	while(token)
	{
		next = token->next;
		free(token->s);
		token->s = NULL;
		free(token);
		token = NULL;
		token = next;
	}
}

void	ft_free_cmd(t_cmd **p_cmd)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	while(cmd)
	{
		next = cmd->nc;
		ft_free_p((void **)&(cmd->params));
		ft_free_p((void **)&(cmd->n));
		cmd->params = NULL;
		cmd->pc = NULL;	
		cmd->ft_envp = NULL;
		cmd->nc = NULL;
		ft_free_p((void **)&(cmd));
		cmd = next;
	}
}

char **ft_envp_copy(char **envp)
{
    int i;
	int	count;
	char **copy;
	
	if (!envp || !*envp)
		return(NULL);
	count = 0;
    while (envp[count])
        count++;
    copy = ft_malloc(sizeof(char *) * (count + 1));
    if (!copy)
        return NULL;
	i = 0;
   	while(i < count)
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return NULL;
        }
		i++;
    }
    copy[i] = NULL;
    return copy;
}

static void	ft_minishell_init(t_main_vars *mv)
{
	g_exit = 0;
	mv->token = NULL;
	mv->cmd = NULL;
	mv->line = NULL;
	mv->ft_envp = NULL;	
}

static void ft_minishell_exit(t_main_vars *mv)
{
	rl_clear_history();
	ft_free_token(&(mv->token));
	ft_free_cmd(&(mv->cmd));
	ft_free_pp((void ***)&(mv->ft_envp));
	ft_free_p((void **)&mv);
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars	*mv;
	
	mv = ft_malloc(sizeof(t_main_vars));
	ft_minishell_init(mv);
	mv->ft_envp = ft_envp_copy(envp); 
	while (1)
	{
		mv->line = readline("minishell > ");
		add_history(mv->line);
		if (ft_strlen(mv->line) > 0)
		{	
			if (ft_strcmp(mv->line, "exit") == 0)
				break;
			if (mv->token = ft_get_token(mv->line))
			{
				if (mv->cmd = get_cmd(mv->token, mv->ft_envp));
					ft_execute(mv->cmd, 0);
			}
			ft_free_p((void **)&(mv->line));
			mv->line = NULL;
		}
	}
	ft_minishell_exit(mv);
}
