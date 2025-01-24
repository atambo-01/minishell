/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/24 10:26:06 by atambo           ###   ########.fr       */
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

void	add_cmd(t_list *token, t_cmd **cmd, char **ft_envp)
{
	t_cmd	*curr;
	t_cmd	*new;

	if (!token || !cmd)
		return ;
	new = ft_malloc(sizeof(t_cmd));
	new->n = ft_strdup (token->s);
	new->params = NULL;
	new->ft_envp = ft_envp;
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

t_list	*add_params(t_list *token, t_cmd *p_cmd)
{
	int		i;
	t_list	*curr;
	t_cmd	*cmd;

	i = 0;
	if (!token || !p_cmd)
		return (NULL);
	curr = token;
	while (curr && (ft_strcmp(curr->s, "|") != 0))
	{
		i++;
		curr = curr->next;
	}
	cmd = get_tail_cmd(p_cmd);
	cmd->params = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (token && (ft_strcmp(token->s, "|") != 0))
	{
		cmd->params[i] = token->s;
		i++;
		token = token->next;
	}
	cmd->params[i] = NULL;
	return (token);
}

t_cmd	*get_cmd(t_list *token, char **ft_envp)
{
	t_cmd	*cmd;

	cmd = NULL;
	add_cmd(token, &cmd, ft_envp);
	token = token->next;
	while (token && token->s)
	{
		if (ft_strcmp(token->s, "|") == 0)
		{
			add_cmd(token, &cmd, ft_envp);
			token = token->next;
			add_cmd(token, &cmd, ft_envp);
			token = token->next;
		}
		else
			token = add_params(token, cmd);
	}
	return (cmd);
}
