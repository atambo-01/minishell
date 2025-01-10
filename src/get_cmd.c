/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:22:05 by atambo            #+#    #+#             */
/*   Updated: 2025/01/10 19:19:05 by atambo           ###   ########.fr       */
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

t_cmd	*add_cmd(t_list *token, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	cmd->n = ft_strcpy(token->s);
	cmd->opt = NULL;
	cmd->params = NULL;
	cmd->prev = prev;
	cmd->next = NULL;
	return (cmd);

}
int	is_opt(void)
{
	return(0);
}

t_cmd	*get_cmd(t_list *token)
{
	t_cmd	*cmd;
	int		p;
	int		o;

	p = 0;
	o = 0;
	cmd = ft_malloc(sizeof(t_cmd));
	cmd->n = ft_strcpy(token->s);
	while(token)
	{
		if (ft_strcmp(token->s, "|") == 0 || 
			ft_strcmp(token->s, ">") == 0 ||
			ft_strcmp(token->s, "<") == 0 ||
			ft_strcmp(token->s, ">>") == 0 ||
			ft_strcmp(token->s, "<<") == 0)
		{
			cmd = add_cmd(token, cmd);
			token = token->next;
			cmd = cmd->next;
			cmd = add_cmd(token, cmd);
		}
		else if (is_opt())
		{
			cmd->opt[o++] = ft_strcpy(token->s);
		}
		else
		{
			cmd->params[p++] = ft_strcpy(token->s);
		}
		token = token->next;
	}
	return (cmd);
}
