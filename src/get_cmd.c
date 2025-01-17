/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/17 14:21:51 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*add_cmd(t_list *token, t_cmd *prev)
{
	t_cmd	*cmd;
	
	if (!token)
		return(NULL);
	cmd = ft_malloc(sizeof(t_cmd));
	cmd->n = ft_strdup (token->s);
	cmd->params = NULL;
	cmd->nc = NULL;
	if (prev)
		prev->nc = cmd;
	return(cmd);
}

t_list	*add_params(t_list *token, t_cmd *cmd)
{
	int		i;
	char	**m;
	t_list	*curr;

	i = 0;
	if(!token)
		return(NULL);
	curr = token;
	while(curr && (ft_strcmp(curr->s, "|") == 0))
	{
		i++;
		curr->next;
	}
	cmd->params = ft_malloc(sizeof(char **) * i + 1);
	i = 0;
	while(token && (ft_strcmp(token->s, "|")) == 0)
	{
		cmd->params[i] = ft_strdup(token->s);
		i++;
		token = token->next; 
	}
	return(token);
}


t_cmd	*get_cmd(t_list *token)
{
	t_cmd	*cmd;
	t_cmd	*head;

	cmd = add_cmd(token, NULL);
	head = cmd;
	token = token->next;
	while(token && token->s)
	{
		if (ft_strcmp(token->s, "|") == 0) 
		{
			cmd->nc = add_cmd(token, cmd);
			cmd = cmd->nc;
			token = token->next;
			cmd->nc = add_cmd(token, cmd);
			cmd = cmd->nc;

		}
		else
		{
			token = add_params(token, cmd);
		}
		token = token->next;
	}
	return (head);
}
