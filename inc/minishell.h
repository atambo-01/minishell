/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/02/12 14:03:22 by atambo            #+#    #+#             */
/*   Updated: 2025/02/16 15:43:27 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

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

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_cmd
{
	char *n;
	struct s_cmd *pc;
	struct s_cmd *nc;
	char *path;
	t_env *env;
	char **params;
	char **redir;
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
	int exit;
	t_env *env;
} t_main_vars;

char	*ft_expand(char *line, t_env *env, const int prev_exi);
int	ft_check_quotes(char *line);
int	ft_cop_syntax(char *line);
void	add_ctrl_op(t_list **p_token, int cop);
void	ft_free_token(t_list **p_token);
void	ft_token_ls(t_list *token);
void	ft_free_cmd(t_cmd **p_cmd);

// parsing.c
void	ft_process_quotes(char ch, t_count *c);
void	ft_handle_pipe(char *line, t_list **token, t_count *c);
void	ft_handle_space_or_end(char *line, t_list **token, t_count *c);
void	ft_get_token_if(char *line, t_list **p_token, t_count *c);
t_list	*ft_get_token(char *line, t_env *env, const int prev_exit);

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
void	add_cmd(t_list *token, t_cmd **cmd, t_env *env);
int	ft_count_params(t_list *token);
void	add_params(t_list **token, t_cmd *p_cmd);
t_cmd	*get_cmd(t_list *token, t_env *env);

// pipe.c
int	ft_pipe(t_cmd *cmd);

// builtins.c
int	ft_builtin(t_cmd *cmd);
int	ft_mtxlen(char **mtx);
int	ft_vfy_name(char *name, char **env);
int	ft_is_valid_name(char *name);
void	print_ex(t_env **envp);

int	ft_echo(t_cmd *cmd);
int	ft_export(char **args, t_env **envp);
int	ft_env(t_cmd *cmd);
int	ft_cd(t_cmd *cmd);
int	ft_pwd(void);
int	ft_unset(t_cmd *cmd);

// execute
int	ft_execute(t_cmd *cmd, int p, int r);

// utils.c
int	ft_cop(char *str);

// env_list
void	ft_add_env_node(t_env *env, char *str);
void	ft_free_env(t_env **p_env);
void	ft_list_env(t_env *env);
void	ft_remove_env_node(t_env **head, char *name);

t_env	*ft_get_env(t_env *env, const char *name);
t_env	*ft_create_env_node(const char *env);
t_env	*ft_create_env_node_2(char *name, char *value);
t_env	*ft_envp_to_list(char **envp);

char	**ft_list_to_envp(t_env *env);

// signal
void	ctrl_c(int sig);
void	ctrl_d(t_main_vars *sig);

//exit 
//void	ft_minishell_exit(t_main_vars **p_mv);

#endif
