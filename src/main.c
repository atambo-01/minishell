/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:30:17 by atambo            #+#    #+#             */
/*   Updated: 2025/01/18 15:14:44 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit = 0;

int	ft_list_size(t_list *head)
{
	int i;

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
	if (!token)
		return ;
	int i = 0;
	while (token)
	{
		if (token && token->s)
			printf("%s", token->s);
		token = token->next;
		if (token && token->s)
			printf("->");
	}
	return ;
}

void	ft_cmd_ls(t_cmd *cmd)
{
	if (!cmd)
		return ;
	int i = 0;
	while (cmd)
	{
		if (cmd && cmd->n)
		{
			printf("cmd_ls = %s\t: ", cmd->n);
			if (cmd->params)
			{
				i = 0;
				while(cmd->params[i])
				{
					printf("%s ", cmd->params[i]);
					i++;
				}
			}
			printf("\n");
		}
		cmd = cmd->nc;
		i++;
		if (cmd && cmd->n)
			printf("\n");
	}
	printf("\n");
	return ;
}

int	main(void)
{
	char *line;
	t_list *token;
	t_cmd *cmd;

	line = ft_strdup("i rock");
	g_exit = 0;
	while (1)
	{
		line = readline("minishell > ");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			token = ft_get_token(line);
		//	ft_token_ls(token);
		//	printf("\n");
			cmd = get_cmd(token);
		//	ft_cmd_ls(cmd);
			ft_execute(cmd, 0);
		}
	}
	ft_free_p((void **)&line);
}
