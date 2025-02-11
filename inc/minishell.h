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
/*   Created: 2025/01/20 12:44:08 by atambo            #+#    #+#             */
/*   Updated: 2025/02/05 02:52:42 by atambo           ###   ########.fr       */
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

// REMOVE THIS !!!!!!
# include <string.h>

extern int g_exit;

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
	char *n;
	char *path;
	char **ft_envp;
	char **params;
	struct s_cmd *pc;
	struct s_cmd *nc;
} t_cmd;

typedef struct s_count
{
	int i;
	int j;
	int k;
	int last;
	int q;
	int temp;
	int end;
} t_count;

typedef struct s_main_vars
{
	t_list *token;
	t_cmd *cmd;
	char *line;
	char **ft_envp;
	int exit;
} t_main_vars;

char	*ft_expand(char *line, char **ft_envp);
int	ft_check_quotes(char *line);
int	ft_ctrl_syntax(char *trim);
void	add_ctrl_op(t_list **p_token, int cop);
void	ft_free_token(t_list **p_token);
void	ft_token_ls(t_list *token);
void	ft_free_cmd(t_cmd **p_cmd);
// parsing.c
void	ft_process_quotes(char ch, t_count *c);
void	ft_handle_pipe(char *line, t_list **token, t_count *c);
void	ft_handle_space_or_end(char *line, t_list **token, t_count *c);
void	ft_get_token_if(char *line, t_list **p_token, t_count *c);
t_list	*ft_get_token(char *line, char **ft_envp);

// parsing_plus.c
void	ft_counter(t_count *c);
void	ft_counter_free(t_count **c);
void	add_token(char *line, t_list **p_token, t_count *c);
void	add_pipe(t_list **p_token);
void	skip_spaces(char *line, t_count *c);

//	get_subtoken.c
void	ft_subtoken_handle_quotes(char *old, char *new, t_count *c);
char	*ft_get_subtoken(char *old);

// get_cmd.c
t_cmd	*get_tail_cmd(t_cmd *cmd);
void	add_cmd(t_list *token, t_cmd **cmd, char **ft_envp);
int	ft_count_params(t_list *token);
void	add_params(t_list **token, t_cmd *p_cmd);
t_cmd	*get_cmd(t_list *token, char **ft_envp);

// pipe.c
int	ft_pipe(t_cmd *cmd, const int prev_exit);

// builtins.c
int	ft_builtin(t_cmd *cm, char ***ft_envp, const int prev_exit);
int	ft_mtxlen(char **mtx);
int	ft_vfy_name(char *name, char ***env);
int	ft_echo(t_cmd *cmd, const int prev_exit);
int	ft_is_valid_name(char *name);
void	ft_export(char **args, char ***env);
void	ft_env(t_cmd *env);
void	print_ex(char **env);
void	ft_export(char **args, char ***env);
void	ft_cd(t_cmd *path);
void	ft_pwd(void);

// execute
int	ft_execute(t_cmd *cmd, int p, const int prev_exit);

// utils.c
int	ft_ctrl_operator(char *str);

#endif
