/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/15 14:25:51 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
int strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{   
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
*/

t_cmd	*add_cmd(t_list *token, t_cmd *prev, char **envp)
{
	t_cmd	*cmd;
	
	if (!token)
		return(NULL);
	cmd = ft_malloc(sizeof(t_cmd));
	cmd->n = ft_strdup (token->s);
	cmd->params = NULL;
	cmd->nc = NULL;
	cmd->envp = envp;
	if (prev)
		prev->nc = cmd;
	return(cmd);
}

void	add_params(t_list *token, char **params)
{
	if (!token || !params)
		return;
	*params = ft_strjoin(*params, token->s);	
}


t_cmd	*get_cmd(t_list *token, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*head;

	cmd = add_cmd(token, NULL, envp);
	head = cmd;
	token = token->next;
	while(token && token->s)
	{
		if (ft_strcmp(token->s, "|") == 0) 
		{
			cmd->nc = add_cmd(token, cmd, envp);
			cmd = cmd->nc;
			token = token->next;
			cmd->nc = add_cmd(token, cmd, envp);
			cmd = cmd->nc;
		}
		else
		{
			add_params(token, &(cmd->params));
		}
		token = token->next;
	}
	return (head);
}
