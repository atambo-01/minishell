/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/15 12:24:43 by atambo            #+#    #+#             */
/*   Updated: 2025/01/15 12:25:27 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int fd[2];
	pid_t pid;
	const char *c0;
	const char *c1;
} t_pipe;

typedef struct s_list
{
	char *s;
	struct s_list *next;
} t_list;

typedef struct s_cmd
{
	char			*n;
	char			**params;
	struct s_cmd	*pc;
	struct s_cmd	*nc;
	struct s_list 	*next;
} t_cmd;

typedef struct s_count
{
	int i;
	int j;
	int k;
	int last;
	int q;
	int temp;
	int aux;
} t_count;

extern int	g_exit;

// get_cmd.c
t_cmd	*add_cmd(t_list *token, t_cmd *prev);
t_cmd	*pipe_cmd(t_list *token, t_cmd *cmd);
t_cmd	*get_cmd(t_list *token);

// parsing.c
void	ft_gt2_a1(char *old, char *new, t_count **p_c);
char	*ft_get_token_2(char *old, t_count *c);
t_list	*ft_get_token_if(char *line, t_list **p_token, t_count **p_c);
t_list	*ft_get_token(char *line);
void	ft_pwd(void);

// parsing_plus.c
t_count	*ft_counter(void);
t_list	*add_token(char *line, t_list **p_token, t_count **p_c);
t_list	*add_pipe(t_list **p_token);
void	skip_spaces(char *line, t_count **p_c);

void	ft_pipe(t_cmd *cmd);
int		ft_builtin(t_cmd *cmd);
int		ft_execute(t_cmd *cmd, int p);

#endif
