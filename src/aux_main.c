/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:47:46 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 18:07:18 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_list_size(t_list *head)
{
	int	i;

	i = 0;
	if (!head)
		return (0);
	while (head->next)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	ft_token_ls(t_list *token)
{
	int	i;

	i = 0;
	if (!token || !token->s)
		return ;
	i = ft_list_size(token);
	while (i-- > -1)
	{
		printf("{%s}", token->s);
		printf(" ");
		token = token->next;
	}
	printf("\n");
	return ;
}

void	ft_free_token(t_list **p_token)
{
	t_list	*token;
	t_list	*next;

	if (!p_token || !*p_token || !(*p_token)->s)
		return ;
	token = *p_token;
	while (token)
	{
		next = token->next;
		free(token->s);
		token->s = NULL;
		free(token);
		token = NULL;
		token = next;
	}
}

void	ft_free_cmd(t_cmd **p_cmd)
{
	int		n;
	t_cmd	*cmd;
	t_cmd	*next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	while (cmd)
	{
		next = cmd->nc;
		n = 0;
		while (cmd->params[n] != NULL)
		{
			free(cmd->params[n]);
			n++;
		}
		ft_free_pp((void ***)&(cmd->params));
		cmd->params = NULL;
		free(cmd->n);
		free(cmd->path);
		cmd->env = NULL;
		free(cmd);
		cmd = next;
	}
	*p_cmd = NULL;
}
