/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 01:21:24 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

t_cmd	*ft_get_tail_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->nc)
		cmd = cmd->nc;
	return (cmd);
}

void	ft_add_cmd(t_token *token, t_cmd **cmd, t_env *env)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd)
		return ;
	new = ft_malloc(sizeof(t_cmd));
	new->n = token->s;
	if (!token->next || ft_cop(token->next->s) == 1)
	{
		new->params = ft_malloc(sizeof(char *) * (2));
		new->params[0] = token->s;
		new->params[1] = NULL;
	}
	new->env = env;
	new->nc = NULL;
	new->pc = NULL;
	new->redir = NULL;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = ft_get_tail_cmd(*cmd);
		curr->nc = new;
		new->pc = curr;
	}
}

int	ft_count_params(t_token *token)
{
	int	i;
	i = 0;
	if (!token)
		return (0);
	while (token)
	{
		if (ft_cop(token->s) == 0)
			i++;
		else if (ft_cop(token->s) > 1)
			token = token->next;
		else if (ft_cop(token->s) == 1)
			break;
		token = token->next;
	}
	return (i);
}

void	ft_add_params(t_token **token, t_cmd *cmd)
{
	int		i;

	if (!*token || !cmd)
		return ;
	i = ft_count_params(*token);
	ft_add_redir(*token, cmd);	
	cmd->params = ft_malloc(sizeof(char *) * (i + 2));
	i = 1;
	cmd->params[0] = cmd->n;
	while (*token && ft_cop((*token)->s) != 1)
	{
		if ((*token)->s && ft_cop((*token)->s) == 0)
		{
			cmd->params[i] = (*token)->s;
			i++;
		}
		else
			*token = (*token)->next;
		if (*token)
			*token = (*token)->next;
	}
	cmd->params[i] = NULL;
}

t_cmd	*ft_get_cmd(t_token *head, t_env *env)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	token = head;
	ft_add_cmd(token, &cmd, env);
	token = token->next;
	while (token && token->s)
	{
		if (token->s && ft_cop(token->s) == 1)
		{
			ft_add_cmd(token, &cmd, env);
			ft_add_cmd(token->next, &cmd, env);
			token = token->next->next;
		}
		else
			ft_add_params(&token, ft_get_tail_cmd(cmd));
	}
	return (cmd);
}






