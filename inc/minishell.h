/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:24:37 by eneto             #+#    #+#             */
/*   Updated: 2025/01/10 19:19:13 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "limits.h"

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}					t_list;

typedef struct s_cmd
{
	char			*n;
	char			**opt;
	char			**params;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

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

//get_cmd.c
t_cmd   *add_cmd(t_list *token, t_cmd *prev);
t_cmd   *pipe_cmd(t_list *token, t_cmd *cmd) ;
t_cmd   *get_cmd(t_list *token);

//parsing.c
void    ft_gt2_a1(char *old, char *new, t_count **p_c);
char    *ft_get_token_2(char *old, t_count *c);
t_list  *ft_get_token_if(char *line, t_list **p_token, t_count **p_c);
t_list  *ft_get_token(char *line);
void	ft_pwd(void);

//parsing_plus.c
t_count *ft_counter(void);
t_list  *add_token(char *line, t_list **p_token, t_count **p_c);
t_list  *add_pipe(t_list **p_token);
void    skip_spaces(char *line, t_count **p_c);


#endif
