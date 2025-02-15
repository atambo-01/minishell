/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/02/15 18:37:02 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	ft_count_params(t_list *token, int r)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && (ft_cop(token->s) != 1))
	{
		if (ft_cop(token->s) == 1)
			break;
		if (r && ft_cop(token->s) != 0)
			break;
		i++;
		token = token->next;
	}
	return (i);
}

void	add_redir(t_list **token, t_cmd* cmd)
{
	int	i;
	
	i = 0;
	cmd->redir = ft_malloc(sizeof(char) * (ft_count_params(*token, 0) + 1));
	while(*token)
	{
		if (ft_cop((*token)->s) == 1)
			break;
		else
		{
			cmd->redir[i] = ft_strdup((*token)->s);
			i++;
		}
		*token = (*token)->next;
	}
	cmd->redir[i] = NULL;

}

void	add_params(t_list **token, t_cmd *p_cmd)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = NULL;
	if (!*token || !p_cmd)
		return ;
	i = ft_count_params(*token, 1);
	cmd = get_tail_cmd(p_cmd);
	cmd->params = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	cmd->params[i] = ft_strdup(cmd->n);
	i++;
	while (*token && (*token)->s)
	{
		if (ft_cop((*token)->s))
			break;
		cmd->params[i] = ft_strdup((*token)->s);
		i++;
		*token = (*token)->next;
	}
	if (*token && ft_cop((*token)->s) > 1)
		add_redir(token, cmd);
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
			token = token->next;
			add_cmd(token, &cmd, env);
			token = token->next;
		}
		else
		{
			add_params(&token, cmd);
		}
	}
	return (cmd);
}






