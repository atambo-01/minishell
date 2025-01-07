/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:24:37 by eneto             #+#    #+#             */
/*   Updated: 2025/01/07 16:42:33 by atambo           ###   ########.fr       */
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

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
	int	last;
	int	q;
	int	temp;
	int	aux;
}		t_count;

char	*ft_cutstr(char *str, char c, int inc);
t_list	*ft_get_token(char *line);

//parsing.c
void    ft_gt2_a1(char *old, char *new, t_count **p_c);
char    *ft_get_token_2(char *old, t_count *c);
t_list  *ft_get_token_if(char *line, t_list **p_token, t_count **p_c);
t_list  *ft_get_token(char *line);


//parsing_plus.c
t_count *ft_counter(void);
t_list  *add_token(char *line, t_list **p_token, t_count **p_c);
t_list  *add_pipe(t_list **p_token);
void    skip_spaces(char *line, t_count **p_c);


#endif
