/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/29 12:26:08 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*get_tail_cmd(t_cmd *cmd)
{
	while (cmd && cmd->nc)
		cmd = cmd->nc;
	return (cmd);
}

void	add_ctrl_cmd(t_list **p_token, t_cmd **cmd, char **ft_envp)
{
	t_cmd	*curr;
	t_cmd	*ctrl;

	if (!p_token || !*p_token || !cmd || !*cmd)
		return ;
	if (!(*p_token)->next)  // Prevent accessing NULL
		return ;
	ctrl = ft_malloc(sizeof(t_cmd));
	if (!ctrl)
		return ;
	ctrl->params = NULL;
	ctrl->ft_envp = ft_envp;
	ctrl->nc = NULL;
	ctrl->pc = NULL;
	curr = get_tail_cmd(*cmd);
	if (curr)
	{
		curr->nc = ctrl;
		ctrl->pc = curr;
	}
	*p_token = (*p_token)->next;
	if (*p_token)  // Prevent unnecessary recursion
		add_cmd(p_token, &ctrl, ft_envp);
}

int	ft_count_params(t_list *token)
{
	int	i;

	i = 0;
	while (token && ft_ctrl_operator(token->s) != 0)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	add_params(t_list **p_token, t_cmd **p_cmd, char **ft_envp)
{
	int		i;
	t_cmd	*cmd;
	t_list	*token;

	if (!p_token || !*p_token || !p_cmd || !*p_cmd)
		return ;
	token = *p_token;
	cmd = *p_cmd;
	i = ft_count_params(token);
	if (i == 0)  // Prevent zero allocation
		return ;
	cmd->params = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd->params)
		return ;
	i = 0;
	if (token) ft_token_ls(token);
	while (token && ft_ctrl_operator(token->s) != 0)
	{
		cmd->params[i] = ft_strdup(token->s);
		if (!cmd->params[i])
			return ;
		i++;
		token = token->next;
	}
	cmd->params[i] = NULL;
	*p_token = token;
	ft_cmd_ls(*p_cmd);
	if (token && ft_ctrl_operator(token->s) == 0)
		add_ctrl_cmd(p_token, p_cmd, ft_envp);
}

void	add_cmd(t_list **p_token, t_cmd **cmd, char **ft_envp)
{
	t_cmd	*curr;
	t_cmd	*new;
	t_list	*token;

	if (!p_token || !*p_token || !cmd)
		return ;
	token = *p_token;
	new = ft_malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->params = NULL;
	new->ft_envp = ft_envp;
	new->nc = NULL;
	new->pc = NULL;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = get_tail_cmd(*cmd);
		if (curr)
		{
			curr->nc = new;
			new->pc = curr;
		}
	}
	add_params(&token, &new, ft_envp);
	*p_token = token;
}

t_cmd	*get_cmd(t_list *token, char **ft_envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!token)
		return (NULL);
	add_cmd(&token, &cmd, ft_envp);
	return (cmd);
}

