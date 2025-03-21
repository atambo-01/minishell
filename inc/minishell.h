#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include <sys/stat.h>
# include <errno.h>

# define COLOR  "\033[0;36m"
# define BOLD   "\x1B[1m"
# define RESET	"\x1B[0m"
# define SHELL	"minishell"			

extern int g_signal;

typedef struct s_pipe
{
	int fd[2];
	pid_t pid;
	const char *c0;
	const char *c1;
} t_pipe;

typedef struct s_token
{
	char *s;
	struct s_token *next;
} t_token;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_cmd
{
	char			*n;
	struct s_cmd	*pc;
	struct s_cmd	*nc;
	char			*path;
	t_env			*env;
	char			**params;
} t_cmd;

typedef struct s_count
{
	int 		i;
	int 		j;
	int 		k;
	int 		last;
	int 		q;
	int 		temp;
	int			start;
	int 		end;
	long long	l;
} t_count;

typedef struct s_main_vars
{
	t_token *token;
	t_cmd 	*cmd;
	char 	*line;
	int		*fd;
	int		fd_c;
	int 	exit;
	t_env 	*env;
} t_main_vars;

typedef struct s_data
{
	int		p_exit;
	int		s_quote;
	t_env	*env;
} t_data;

typedef struct s_pipe_data
{
    int     fd[2];
    int     prev_read_fd;
    int     i;
    int     cmd_count;
    pid_t   *pids;
	t_token	*token;
} t_pipe_data;

// main.c +
int		ft_check_quotes(char *line);
int		ft_cop_syntax(char *line);
void	ft_add_ctrl_op(t_token **p_token, int cop);
void	ft_free_token(t_token **p_token);
void	ft_token_ls(t_token *token);
void	ft_cmd_ls(t_cmd *cmd);
void	ft_free_cmd(t_cmd **p_cmd);
void    ft_shell_init(t_main_vars *mv, char **envp, int ac, char **av);
void    ft_main_while_free(t_main_vars *mv);
void	ft_exit_update(int *i);

//expand.c 
char	*ft_expand(char *line, t_env *env, const int p_exit, int s_quote);
char	*ft_exp_env(t_count *c, char *line, char **exp_line, t_env *env);
void    ft_exp_exit(char **exp_line, t_count *c, int p_exit);

// parsing.c
void	ft_process_quotes(char ch, t_count *c);
void	ft_handle_pipe(char *line, t_token **token, t_count *c);
void	ft_handle_space_or_end(char *line, t_token **token, t_count *c);
void	ft_get_token_if(char *line, t_token **p_token, t_count *c);
char 	*ft_pre_get_token(char *line, t_env *env, int exit, t_main_vars *mv);
t_token	*ft_token(char *line, t_env *env, int prev_exit, t_main_vars *mv);

// parsing_plus.c
void	ft_counter(t_count *c);
void	ft_counter_free(t_count **c);
void	ft_add_token(char *line, t_token **p_token, t_count *c);
void	ft_add_pipe(t_token **p_token);
void	ft_skip_spaces(char *line, t_count *c);

//	get_subtoken.c
void	ft_subtoken_handle_quotes(char *old, char *new, t_count *c);
char	*ft_get_subtoken(char *old);

// get_cmd.c
t_token	*ft_add_cmd(t_token *token, t_cmd **cmd, t_env *env);
void	ft_add_params(t_token **token, t_cmd *p_cmd);
t_cmd	*ft_get_cmd(t_token *token, t_env *env);
t_token *ft_add_pipe_cmd(t_token *token, t_cmd **cmd, t_env *env);

// get_cmd_aux.c
t_cmd	*ft_get_tail_cmd(t_cmd *cmd);
int		ft_count_params(t_token *token);
void    ft_add_params_single(t_token ** token, t_cmd *cmd);

// pipe.c
t_token *ft_get_pipe(t_token *token);
int		ft_count_cmd(t_cmd *cmd);
int		ft_pipe(t_main_vars *mv);
void    ft_restore_fd(int fd[]);
int 	ft_bckp_fd(int fd[]);

// builtins.c
int 	ft_strstr(char *str, char *str_find);
int		ft_builtin(t_cmd *cmd);
int		ft_mtxlen(char **mtx);
int		ft_vfy_name(char *name, char **env);
int		ft_is_valid_name(char *name);
int		ft_print_ex(t_env **envp);
int		ft_run_builtin(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_export(char **args, t_env **envp);
int		ft_env(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(void);
int		ft_unset(t_cmd *cmd);

// ft_get_path
int  	ft_get_path(t_cmd *cmd);
int		ft_get_path_aux(char  *path);
// execute
int		ft_execute(t_cmd *cmd);

// utils.c
int		ft_cop(char *str);

// env_list
void	ft_add_env_node(t_env *env, char *str);
void	ft_free_env(t_env *p_env);
void	ft_token_env(t_env *env);
void	ft_remove_env_node(t_env **head, char *name);

char	*ft_getenv(t_env *env, const char *name);
t_env	*ft_create_env_node(const char *env);
t_env	*ft_create_env_node_2(char *name, char *value);
t_env	*ft_envp_to_list(char **envp);

char	**ft_token_to_envp(t_env *env);

// signal
void	ft_ctrl_c(int  sig);
void	ft_ctrl_d(t_main_vars *sig);
void	ft_signal(int o_int, int o_quit);
void    ft_execve_sigint(int sig);
void    ft_execve_sigquit(int sig);
void    ft_execve_sigquit_2(int sig);
void	ft_builtin_sigint(int sig);
void	ft_heredoc_sigint(int sig);

// redir.c
int		ft_get_redir(t_main_vars *mv, t_token *head, int **fd, int *count);
int 	ft_redir_append(t_token *token, int fd[], int *i_fd);
int 	ft_redir_in(t_token *token, int fd[], int *i_fd);
int 	ft_redir_out(t_token *token, int fd[], int *i_fd);


// redir_heredoc.c
int     ft_heredoc(t_main_vars *mv, t_token *token, int fd[], int *i_fd);
void    heredoc_child(t_main_vars *mv, int fd[], int i_fd, char *delimiter);

// redir_utils.c
int 	ft_count_redir(t_token *token);
int 	ft_mod_fd(t_main_vars *mv, t_token *token, int fd[], int *i_fd);
int 	ft_bckp_fd(int fd[]);
void    ft_close_fd(int fd[], int i_fd);
void    ft_restore_fd(int fd[]);


// exit
int 	ft_exit(t_main_vars *mv);
int 	ft_exit_atoi(char *str);
int 	handle_number(char *str, t_count *c);
int 	handle_quotes(char *str, t_count *c);
int		handle_space_and_signs(char *str, t_count *c);
int 	ft_convert(long long l);
int		is_quote(char c);
int		handle_numbers(char *str, t_count *c);
void	handle_sign(char *str, t_count *c);
void    ft_exit_free(t_main_vars *mv);

void	free_on_add_env_node(char *name, char *value);

//void	ft_minishell_exit(t_main_vars **p_mv);

#endif
