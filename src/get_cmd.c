/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/31 12:38:05 by atambo           ###   ########.fr       */
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
	new->params = ft_malloc(sizeof(char **) * 2);
	new->params[0] = ft_strdup(new->n);
	new->params[1] = NULL;
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

int	ft_count_params(t_list *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && (ft_ctrl_operator(token->s) != 0))
	{
		i++;
		token = token->next;
	}
	return (i);
}

t_list	*add_params(t_list *token, t_cmd *p_cmd)
{
	int		i;
	t_list	*curr;
	t_cmd	*cmd;

	i = 0;
	if (!token || !p_cmd)
		return (NULL);
	free(p_cmd->params[0]);
	free(p_cmd->params);
	i = ft_count_params(token);
	cmd = get_tail_cmd(p_cmd);
	p_cmd->params = ft_malloc(sizeof(char *) * (i + 3));
	p_cmd->params[0] = cmd->n;
	i = 1;
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
