/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_get_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:15:33 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 18:26:47 by eneto            ###   ########.fr       */
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
	while (token && (ft_cop(token->s) != 1))
	{
		if (ft_cop(token->s) == 0)
			i++;
		else
			token = token->next;
		if (token)
			token = token->next;
	}
	return (i);
}
