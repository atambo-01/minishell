/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:30:17 by atambo            #+#    #+#             */
/*   Updated: 2025/01/18 17:43:39 by atambo           ###   ########.fr       */
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

void	ft_free_token(t_list **p_token)
{
	t_list	*token;

	token = *p_token;
	if (!token || !token->s)
		return;
	while(token->next)
	{
		ft_free((void **)&token);
		token = token->next;
	}
	ft_free((void **)&token);
}

void	ft_free_cmd(t_cmd **p_cmd)
{
	t_cmd	*cmd;
	t_cmd	*next;

	if (!p_cmd || !*p_cmd)
		return ;
	cmd = *p_cmd;
	while(cmd)
	{
		next = cmd->nc;
		ft_free_pp((void ***)&(cmd->params));
		ft_free_pp((void ***)&(cmd->envp));
		ft_free_p((void **)&(cmd->n));
		ft_free_p((void **)&(cmd->pc));
		cmd = cmd->nc;
		if (cmd->pc)
			ft_free_p((void **)&(cmd->pc));
	}
	ft_free_p((void **)&cmd);
}

char **ft_envp_copy(char **envp)
{
    int i = 0;
    char **copy;

    // Count the number of environment variables
    while (envp[i])
        i++;

    // Allocate memory for the copy
    copy = malloc((i + 1) * sizeof(char *));
    if (!copy)
        return NULL;

    // Duplicate each environment variable
    for (i = 0; envp[i]; i++)
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            // Free already allocated strings on failure
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return NULL;
        }
    }
    copy[i] = NULL; // Null-terminate the array
    return copy;
}

int	main(void)
{
	char	*line;
	t_list	*token;
	t_cmd	*cmd;

	line = ft_strdup("i rock");
	g_exit = 0;
	while (1)
	{
		line = readline("minishell > ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strcmp(line, "exit") == 0)
				break;
			add_history(line);
			token = ft_get_token(line);
		//	ft_token_ls(token);
		//	printf("\n");
			cmd = get_cmd(token);
		//	ft_cmd_ls(cmd);
			ft_execute(cmd, 0);
			ft_free_p((void **)&line);
		}
	}
	ft_free_p((void **)&line);
	ft_free_token(token);
	ft_free_cmd(cmd);
}
