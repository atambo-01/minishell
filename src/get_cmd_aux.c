/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:38:44 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 16:54:50 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_params_single(t_token **token, t_cmd *cmd)
{
	cmd->params = ft_malloc(sizeof(char *) * 2);
	cmd->params[0] = ft_get_subtoken(cmd->n);
	cmd->params[1] = NULL;
	*token = (*token)->next;
}

t_cmd	*ft_get_tail_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->nc)
		cmd = cmd->nc;
	return (cmd);
}

int	ft_count_params(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token)
	{
		if (ft_cop(token->s) == 0)
			i++;
		else if (ft_cop(token->s) > 1)
			token = token->next;
		else if (ft_cop(token->s) == 1)
			break ;
		if (token)
			token = token->next;
	}
	return (i);
}
