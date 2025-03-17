/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:24:04 by atambo            #+#    #+#             */
/*   Updated: 2025/03/17 11:22:47 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token *ft_get_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	if (ft_cop(token->s) == 1)
		token = token->next;
	while(token)
	{
		if (ft_cop(token->s) == 1)
			return(token);
		token = token->next;
	}
	return(NULL);
}

int	ft_pipe_stdout(t_main_vars *mv, int (*fd)[2], t_token *token, int i)
{
	int status;

	status = 0;
	dup2(fd[i][1], STDOUT_FILENO);
	if (ft_count_redir(token))
		status = ft_get_redir(mv, token, &(mv->fd), &(mv->fd_c));
	return (status);
}

int ft_pipe_stdin(t_main_vars *mv, int (*fd)[2], t_token *token, int i)
{
	int status;

	status = 0;
	dup2(fd[i - 1][0], STDIN_FILENO);
	if (ft_count_redir(token))
		status = ft_get_redir(mv, token, &(mv->fd), &(mv->fd_c));
	return (status);
}
/*
int	ft_handle_fork(t_main_vars* mv, t_cmd *cmd, int (*fd)[2], t_token *token, int i)
{
	pid_t	pid;
	int 	status;
	
	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
//		ft_restore_fd(mv->fd);
	//	if (mv->cmd != cmd)
		if (cmd != mv->cmd)
		{
			printf("--------------------\n");
			printf("i == %d\n", i);
			printf("--------------------\n");
			ft_cmd_ls(cmd);
		//	status = ft_pipe_stdin(mv, fd, token, i);
		}
		if (cmd->nc != NULL)
		{
			printf("--------------------\n");
			printf("i == %d\n", i);
			printf("--------------------\n");
			ft_cmd_ls(cmd);
		//	status = ft_pipe_stdout(mv, fd, token, i);
		}
	//	ft_execute(cmd);
		exit (status);
	}
	waitpid(pid, &status, 0);
	return (status);
}

int	ft_pipe(t_main_vars *mv, t_cmd *cmd, t_token *token)
{
	t_cmd	*curr;
	int		i;
	int		status;
	int		fd[100][2];

	status = -1;
	curr = cmd;
	i == 0;
	while(curr)
	{
		if (pipe(fd[i]) == -1)
			return(ft_perror("minishell: pipe fd error\n", 1));
		ft_handle_fork(mv, curr, fd, token, i);
		curr = curr->nc;
		if (ft_cop(curr->n) == 1 && curr->nc)
			curr = curr->nc;
		token = ft_get_pipe(token);
	//	ft_restore_fd(mv->fd);
		i++;
	}
	return(status);
}
*/
int ft_handle_fork(t_main_vars* mv, t_cmd *cmd, int (*fd)[2], t_token *token, int i)
{
    pid_t   pid;
    int     status = 0;
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) // Child process
    {
        // Handle input redirection (all except first command)
        if (cmd != mv->cmd) 
        {
            status = ft_pipe_stdin(mv, fd, token, i);
            close(fd[i-1][1]); // Close write end of previous pipe
        }
        
        // Handle output redirection (all except last command)
        if (cmd->nc != NULL)
        {
            status = ft_pipe_stdout(mv, fd, token, i);
            close(fd[i][0]);   // Close read end of current pipe
        }
        
        ft_execute(cmd);  // Execute the command
        exit(status);
    }
    // Parent process
    if (i > 0)
        close(fd[i-1][0]);     // Close previous read end
    if (cmd->nc != NULL)
        close(fd[i][1]);       // Close current write end
        
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

int ft_pipe(t_main_vars *mv, t_cmd *cmd, t_token *token)
{
    t_cmd   *curr = cmd;
    int     i = 0;
    int     status = 0;
    int     fd[100][2];

    while (curr)
    {
        if (curr->nc && pipe(fd[i]) == -1) // Only create pipe if there's a next command
            return (ft_perror("minishell: pipe fd error\n", 1));
            
        status = ft_handle_fork(mv, curr, fd, token, i);
        
        curr = curr->nc;
        if (curr && ft_cop(curr->n) == 1 && curr->nc)
            curr = curr->nc;
        token = ft_get_pipe(token);
        i++;
    }
    return (status);
}
