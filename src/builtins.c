/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:33:06 by atambo            #+#    #+#             */
/*   Updated: 2025/02/21 18:33:28 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo_flags(char *str, char *flags)
{
	ft_memset(flags, 0, 53);
	while (*str)
	{
		if (*str == 'n')
			flags['n' - 'a'] = 1;
		else
		{
			ft_memset(flags, 0, 53);
			return (0);
		}
		str++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		n;
	char	flags[53];

	if (!cmd)
		exit(1);
	n = 1;
	ft_memset(flags, 0, 53);
	if (!cmd->params[1])
	{
		printf("\n");
		exit(0);
	}
	if (cmd->params[1][0] == '-' && cmd->params[1][1])
		n += ft_echo_flags(&(cmd->params[1][1]), flags);
	while (cmd->params[n])
	{
		printf("%s", cmd->params[n]);
		n++;
		if (cmd->params[n])
			printf(" ");
	}
	if (flags['n' - 'a'] == 0)
		printf("\n");
	exit(0);
}

int	ft_pwd(void)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX);
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	ft_free_p((void **)&buff);
	exit(0);
}

int	ft_cd(t_cmd *cmd)
{
	t_env	*home;

	if (cmd->params[2])
		exit(ft_perror("cd: too many arguments\n", 1));
	if (!cmd->params[1])
	{
		home = ft_get_env(cmd->env, "HOME");
		if (!home || !home->value)
			exit(ft_perror("minishell: cd: HOME not set.", 1));
		chdir(home->value);
		exit (0);
	}
	chdir(cmd->params[1]);
	exit(0);
}

int ft_run_builtin(t_cmd *cmd)
{
    pid_t   pid;
    int     status;
    char    **env_p;

    status = 0;
    env_p = NULL;
    pid = fork();
    ft_signal((int []){0, 0, 1, 0, 0});
    if (pid == -1)
        return (ft_perror("fork", -1));
    if (pid == 0)
    {
        env_p = ft_list_to_envp(cmd->env);
        if (!env_p || !*env_p)
            exit(1);
        if (ft_builtin(cmd) == -1)
            exit(2);
    }
    else
    {
        ft_signal((int []){0, 0, 0, 1, 1});
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            status = 128 + WTERMSIG(status);
    }
    return (status);
}  

int	ft_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->n, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->n, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->n, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->n, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->n, "export") == 0)
		ft_export(cmd->params, &(cmd->env));
	/*else if (ft_strcmp(cmd->n, "exit") == 0)
		ft_exit(cmd->n, prev_exit);
*/
	exit (127);
}
