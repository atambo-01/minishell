/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:44:29 by atambo            #+#    #+#             */
/*   Updated: 2025/03/02 01:27:55 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

void	ft_exit_free(t_main_vars *mv)
{
	if (!mv)
		return ;
	ft_restore_fd(mv->fd);
	ft_free_env(&(mv->env));
	free(mv->line);
	rl_clear_history();
	ft_free_token(&(mv->token));
	free(mv->fd);
	mv->fd = NULL;
}

int	ft_exit_atoi(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] == '-' && (i == 0 || i == 1))
			return (-1);
		else if (str[i] == '+' && (i == 0 || i == 1))
			i++;
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
		{
			if (!ft_isdigit(str[i]))
				return (-1);
			num = num * 10 + (str[i] - '0');
			if (num > INT_MAX)
				return (-1);
		}
		i++;
	}
	return (num);
}

int	ft_exit(t_main_vars *mv)
{
	int	status;
	int	num;

	status = 0;
	num = 0;
	if (ft_strcmp(mv->token->s, "exit") != 0)
		return (0);
	if (mv->token->next)
	{
		if (mv->token->next->next)
			status = 2;
		num = ft_exit_atoi(mv->token->next->s);
	}
	if (status != 2)
		ft_exit_free(mv);
	printf("exit\n");
	if (num == -1)
		status = ft_perror("minishell: exit: need a numeric argument\n", 1);
	else if (status == 2)
		return (ft_perror("minishell: exit: to many arguments\n", status));
	else
		status = num;
	exit(status);
}

void	ft_main_nest(t_main_vars *mv)
{
	int	redir;

	mv->cmd = ft_get_cmd(mv->token, mv->env);
	ft_bckp_fd(mv->fd);
	if (mv->cmd != NULL)
	{
		if (ft_get_pipe(mv->token) != NULL)
			ft_pipe(mv, mv->cmd, mv->token);
		else
		{
			if (ft_count_redir(mv->token) > 0)
			{
				redir = ft_get_redir(mv->token, &(mv->fd), &(mv->fd_c));
				if (redir == 0)
					mv->exit = ft_execute(mv->cmd);
				else
					mv->exit = redir;
			}
			else
				mv->exit = ft_execute(mv->cmd);
		}
	}
	else if (ft_count_redir(mv->token) > 0)
		ft_get_redir(mv->token, &(mv->fd), &(mv->fd_c));
}

int	main(int ac, char **av, char **envp)
{
	t_main_vars	mv;

	ft_shell_init(&mv, envp, ac, av);
	while (1)
	{
		ft_signal((int []){1, 1, 0, 0, 0, 0});
		ft_main_while_free(&mv);
		mv.line = readline(COLOR BOLD "攻殻_機動隊 > " RESET);
		ft_ctrl_d(&mv);
		if (ft_strlen(mv.line) == 0)
			continue ;
		mv.exit = ft_exit_update(mv.exit);
		add_history(mv.line);
		mv.token = ft_token(mv.line, mv.env, mv.exit);
		if (!mv.token)
			continue ;
		if (ft_exit(&mv) == 2)
			mv.exit = 2;
		else
			ft_main_nest(&mv);
	}
}
