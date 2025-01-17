/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/17 21:19:50 by atambo           ###   ########.fr       */
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
	t_list	*curr;

	i = 0;
	if(!token)
		return(NULL);
	curr = token;
	while(curr && curr->s) 
	{
		if (ft_strcmp(curr->s, "|") == 0)
			break;
		i++;
		curr = curr->next;
	}
	cmd->params = ft_malloc(sizeof(char *) * i + 1);
	i = 0;
	printf("HERE! curr->s = %s\n", curr->s);
	while(token && token->s)
	{
		if (ft_strcmp(token->s, "|") == 0)
			break;
		cmd->params[i] = token->s;
		i++;
		token = token->next;
	}
	cmd->params[i] = NULL;
	return(token);
}


t_cmd	*get_cmd(t_list *token)
{
	t_cmd	*cmd;
	t_cmd	*head;
	/*	
	 */

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
			token = token->next;
		}
		else
		{
			token = add_params(token, cmd);
		}
	}
	return (head);
}
