/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:44:29 by atambo            #+#    #+#             */
/*   Updated: 2025/03/05 17:17:42 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

void	ft_exit_free(t_main_vars *mv)
{
	if (!mv)
		return ;
	ft_restore_fd(mv->fd);
	rl_clear_history();
	ft_free_env(&(mv->env));
	free(mv->line);
	ft_free_token(&(mv->token));
	free(mv->fd);
	mv->fd = NULL;
}

int ft_convert(long long l)
{
	if (l < 0)
		return (256 + (int)(l % 256));
	else if (l > 255)
	{	
		return ((int)(l % 256));
	}
	return ((int)l);
}


int	ft_exit_atoi(char *str)
{
	t_count	c;

	ft_counter(&c);
	if (!str || !*str)
		return (-1);
	while(*str == ' ' || *str == '\t' || *str == '"' || *str == '\'')
		str++;
	c.j = 1;
	if (str[c.i] == '-' || str[c.i] == '+')
	{
		if (str[c.i] == '-')
			c.j = -1;
		(c.i)++;
	}
	while (str[c.i] || str[c.i] == '"' || str[c.i] == '\'')
	{
		if (str[c.i] < '0' || str[c.i] > '9')
			return (-1);
		c.l = c.l * 10 + (str[c.i] - '0');
		if (c.l > LONG_MAX)
			return(-1);
		(c.i)++;
	}
	return (ft_convert(c.j * c.l));
}

int	ft_exit(t_main_vars *mv)
{
	int	num;
	int	status;

	status = 0;
	num = mv->exit;
	if (ft_strcmp(mv->token->s, "exit") != 0)
		return (0);
	printf("exit\n");
	if (mv->token->next)
	{
		if (mv->token->next->next)
			status = 1;
		num = ft_exit_atoi(mv->token->next->s);
		if (status != 1)
			ft_exit_free(mv);
		if (num == -1)
			exit (ft_perror("minishell: exit: need a numeric argument\n", 2));
		else if (status == 1)
			return (ft_perror("minishell: exit: to many arguments\n", status));
	}
	exit(num);
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
	int i = -1;
	while (1)
	{
		i++;
		ft_signal((int []){1, 1, 0, 0, 0, 0});
		ft_main_while_free(&mv);
		mv.line = readline(COLOR BOLD "攻殻_機動隊 > " RESET);
	 	/*
		*/
		/*
		if (i == 0)
		{
			mv.line = ft_strdup("exit 42");
		}
		if (i == 1)
		{
			mv.line = ft_strdup("");
			sleep(2);
		}
		if (i == 2)
		{
			mv.line = ft_strdup("");
			sleep(2);
		}
		*/
		ft_ctrl_d(&mv);
		if (ft_strlen(mv.line) == 0)
			continue ;
		mv.exit = ft_exit_update(mv.exit);
		add_history(mv.line);
		mv.token = ft_token(mv.line, mv.env, mv.exit, &mv);
		if (!mv.token)
			continue ;
		if (ft_exit(&mv) == 1)
			mv.exit = 1;
		else
			ft_main_nest(&mv);
	}
}
