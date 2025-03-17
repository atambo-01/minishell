/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_auxiliary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:55:26 by atambo            #+#    #+#             */
/*   Updated: 2025/03/01 20:26:33 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     ft_token_size(t_token *head)
{
        int     i;

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

void    ft_token_ls(t_token *token)
{
        int     i;

        i = 0;
        if (!token || !token->s)
                return ;
        i = ft_token_size(token);
        while (i-- > -1)
        {
                printf("{%s}", token->s);
                printf(" ");
                token = token->next;
        }
        printf("\n");
        return ;
}

void    ft_cmd_ls(t_cmd *cmd)
{
        int     i;

        if (!cmd)
                return ;
        i = 0;
        while (cmd)
        {
                if (cmd && cmd->n)
                {
                        printf("cmd_ls = %s\t:", cmd->n);
                        if (cmd->params)
                        {
                                i = 0;
                                while (cmd->params[i])
                                        printf(" {%s} ", cmd->params[i++]);
                        }
                        printf("\n");
                }
                cmd = cmd->nc;
                i++;
                if (cmd && cmd->n)
                        printf("\n");
        }
        return ;
}
