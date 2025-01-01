/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:24:37 by eneto             #+#    #+#             */
/*   Updated: 2024/12/19 19:24:37 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}					t_list;

typedef struct s_tree
{
	char			*cmd;
	t_list			*opt;
	t_list			*params;
	struct s_tree	*next_cmd;
}					s_tree;

char	*ft_cutstr(char *str, char c, int inc);
t_list	*ft_get_token(char *line);
char	*ft_get_token_2(char **p_old);

#endif
