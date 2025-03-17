/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:50:25 by atambo            #+#    #+#             */
/*   Updated: 2025/03/17 15:54:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_cmd(t_cmd *cmd)
{
	int		count;
	t_cmd	*curr;

	count = 0;
	curr = cmd;
	while (curr)
	{
		if (ft_cop(curr->n) == 0)
			count++;
		curr = curr->nc;
	}
	return (count);
}

t_token	*ft_get_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	if (ft_cop(token->s) == 1)
		token = token->next;
	while (token)
	{
		if (ft_cop(token->s) == 1)
			return (token);
		token = token->next;
	}
	return (NULL);
}
