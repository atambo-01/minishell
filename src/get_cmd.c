/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 16:28:42 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_get_tail_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->nc)
		cmd = cmd->nc;
	return (cmd);
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

t_token	*ft_add_cmd(t_token *token, t_cmd **cmd, t_env *env)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd || ft_cop(token->s) != 0)
		return (token);
	new = ft_malloc(sizeof(t_cmd));
	new->n = token->s;
	new->env = env;
	new->nc = NULL;
	new->pc = NULL;
	ft_add_params(&token, new);
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = ft_get_tail_cmd(*cmd);
		curr->nc = new;
		new->pc = curr;
	}
	return (token); // Return the last token processed
}

void	ft_add_params(t_token **token, t_cmd *cmd)
{
	int		i;

	if (!*token || !cmd)
		return;
	i = ft_count_params(*token);
	if (i == 1) // If no parameters, only include command name
	{
		cmd->params = ft_malloc(sizeof(char *) * 2);
		cmd->params[0] = cmd->n;
		cmd->params[1] = NULL;
		*token = (*token)->next;
		return;
	}
	cmd->params = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
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

t_token	*ft_add_pipe_cmd(t_token *token, t_cmd **cmd, t_env *env)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd || ft_cop(token->s) != 1)
		return (token);
	new = ft_malloc(sizeof(t_cmd));
	new->n = token->s;
	new->env = env;
	new->nc = NULL;
	new->pc = NULL;
	new->params = NULL;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = ft_get_tail_cmd(*cmd);
		curr->nc = new;
		new->pc = curr;
	}
	token = token->next;
	return (token);
}

t_cmd	*ft_get_cmd(t_token *head, t_env *env)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	token = head;
	while (token && token->s)
	{
		if 		(ft_cop(token->s) > 1)
			token = token->next->next;
		else if (ft_cop(token->s) == 1)
			token = ft_add_pipe_cmd(token, &cmd, env);
		else if (ft_cop(token->s) == 0) // Only process if it's a command
			token = ft_add_cmd(token, &cmd, env);
		else
			token = token->next;
	}
	return (cmd);
}

