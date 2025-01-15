/*                                                                            */
/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:09:36 by eneto             #+#    #+#             */
/*   Updated: 2025/01/09 14:10:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int		ft_list_size(t_list *head)
{
	int	i;

	i = 0;
	if (!head)
		return(0);
	while(head->next)
	{
		i++;
		head = head->next;
	}
	return(i);
}

void	ft_token_ls(t_list *token)
{
	if (!token)
		return;
	int  i = 0;
	while(token)
	{
		if (token && token->s)
			printf("%s", token->s);
		token = token->next;
		if (token && token->s)
			printf("->");
	}
	return;
}

void	ft_cmd_ls(t_cmd *cmd)
{
	if (!cmd)
		return;
	int  i = 0;
	while(cmd)
	{
		if (cmd && cmd->n)
		{
			printf("cmd_ls = %s\t: ", cmd->n);
			if (cmd->params)
			{
				ft_token_ls(cmd->params);
			}
			printf("\n");
		}
		cmd = cmd->nc;
		i++;
		if (cmd && cmd->n)
			printf("\n");
	}
	printf("\n");
	return;
}


int	main(void)
{
	char	*line;
	t_list	*token;
    t_cmd   *cmd;
	while(1)
	{	
		line = readline("minishell > ");
		printf("%s\n", line);
		token = ft_get_token(line);
		ft_token_ls(token);
		printf("\n");
		add_history(line);
        cmd = get_cmd(token);
		ft_cmd_ls(cmd);
		//printf("params = %s\n", cmd->params->s);
	}
}
