/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/02/21 18:18:36 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_cmd(t_list *token, t_cmd **cmd, t_env *env)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd)
		return ;
	new = ft_malloc(sizeof(t_cmd));
	new->n = ft_strdup(token->s);
	if (!token->next || ft_cop(token->next->s))
	{
		new->params = (char **)ft_malloc(sizeof(char *) * 2);
		new->params[0] = strdup(new->n);
		new->params[1] = NULL;
	}
	new->env = env;
	new->nc = NULL;
	new->pc = NULL;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = get_tail_cmd(*cmd);
		curr->nc = new;
		new->pc = curr;
	}
}

void	add_redir(t_list *token, t_cmd *cmd)
{
	int	i;
	int	w;

	if (!token || !cmd || ((i = ft_count_redir(token)) <= 0))
		return ;
	cmd->redir = ft_malloc(sizeof(char) * (i + 1));
	printf("redir count  = %d\n", i);
	i = 0;
	while (token)
	{
		if (ft_cop(token->s) >= 1)
		{
			cmd->redir[i] = strdup(token->s);
			printf("add_redir = %s\n", cmd->redir[i]);
			i++;
			token = token->next;
			cmd->redir[i] = strdup(token->s);
			printf("add_redir = %s\n", cmd->redir[i]);
			i++;
			printf("i  = %d\n", i);
		}
		if (token)
			token = token->next;
		printf("redir[0] = %s\n", cmd->redir[0]);
		printf("---------------------------------------------\n");
	}
	cmd->redir[i] = NULL;
	w = 0;
	while (cmd->redir[w])
	{
		printf("%s\n", cmd->redir[w]);
		w++;
	}
}

void	add_params(t_list **token, t_cmd *cmd)
{
	int	i;

	if (!*token || !cmd)
		return ;
	i = ft_count_params(*token);
	add_redir(*token, cmd);
	cmd->params = ft_malloc(sizeof(char *) * (i + 2));
	i = 1;
	cmd->params[0] = ft_strdup(cmd->n);
	while (*token && ft_cop((*token)->s) != 1)
	{
		if ((*token)->s && ft_cop((*token)->s) == 0)
		{
			cmd->params[i] = ft_strdup((*token)->s);
			i++;
		}
		else
			*token = (*token)->next;
		if (*token)
			*token = (*token)->next;
	}
	cmd->params[i] = NULL;
}

t_cmd	*get_cmd(t_list *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = NULL;
	add_cmd(token, &cmd, env);
	token = token->next;
	while (token && token->s)
	{
		if (token->s && ft_cop(token->s) == 1)
		{
			add_cmd(token, &cmd, env);
			add_cmd(token->next, &cmd, env);
			token = token->next->next;
		}
		else
		{
			add_params(&token, get_tail_cmd(cmd));
		}
	}
	return (cmd);
}
