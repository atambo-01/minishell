/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/02/22 10:47:44 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

t_cmd	*get_tail_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->nc)
		cmd = cmd->nc;
	return (cmd);
}

void	add_cmd(t_list *token, t_cmd **cmd, t_env *env)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd)
		return ;
	new = ft_malloc(sizeof(t_cmd));
	new->n = ft_strdup(token->s);
	if (!token->next || ft_cop(token->next->s) == 1)
	{
		new->params = ft_malloc(sizeof(char *) * (2));
		new->params[0] = strdup(token->s);
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
		curr = get_tail_cmd(*cmd);
		curr->nc = new;
		new->pc = curr;
	}
}

int	ft_count_redir(t_list *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && (ft_cop(token->s) != 1))
	{
		if (ft_cop(token->s) > 1)
		{
			i += 2;
			token = token->next;
		}	
		token = token->next;
	}
	return (i);
}

int	ft_count_params(t_list *token)
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

void	add_redir(t_list *token, t_cmd *cmd)
{
	int	i;
	
	if (!token || !cmd || ((i = ft_count_redir(token)) <= 0))
		return ;
	cmd->redir = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(token)
	{
		if (ft_cop(token->s) >= 1)
		{
			cmd->redir[i] = strdup(token->s);
			i++;
			token = token->next;
			cmd->redir[i] = strdup(token->s);
			i++;
		}
		if (token)
			token = token->next;
	}
	cmd->redir[i] = NULL;
}

void	add_params(t_list **token, t_cmd *cmd)
{
	int		i;

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
			add_params(&token, get_tail_cmd(cmd));
	}
	return (cmd);
}






