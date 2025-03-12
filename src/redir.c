/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:20:24 by atambo            #+#    #+#             */
/*   Updated: 2025/03/11 22:51:40 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void handle_heredoc_child(t_main_vars *mv, int fd[], int i_fd, char *delimiter)
{
    char *line;
	char *temp;

    close(fd[i_fd]);
    while (g_signal == 0)
    {
        temp = readline("> ");
		line = ft_expand(temp, mv->env, mv->exit, 1);
		free(temp);
        if (!line || g_signal == SIGINT || strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd[i_fd + 1], line, strlen(line));
        write(fd[i_fd + 1], "\n", 1);
        free(line);
    }
    close(fd[i_fd + 1]);
    free(delimiter);
    exit(0);
}

t_token  *next_heredoc(t_token *token)
{
	if (!token)
		return (NULL);
	while(token)
	{
		if (ft_cop(token->s) == 5)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int ft_heredoc(t_main_vars *mv, t_token *token, int fd[], int *i_fd)
{
    pid_t 	pid;
    int 	status;
	char 	*temp;
	t_token *curr;

	status = 0;
    if (pipe(&fd[*i_fd]) == -1)
		return (ft_perror("minshell: heredoc: pipe\n", 1));
	curr = token;
	while(curr)
	{
		printf("while loop\n");
		temp = ft_get_subtoken(curr->next->s);
		pid = fork();
		if (pid == -1)
			return (ft_perror("minshell: heredoc: fork\n", 1));
		if (pid == 0)
		{	
			handle_heredoc_child(mv, fd, *i_fd, temp);
		}
		close(fd[*i_fd + 1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			status = (130);
		if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
			status =  (ft_perror("minshell: heredoc: dup2\n", 1));
		curr = next_heredoc(curr->next);
	}
	(*i_fd) += 2;
	printf("heredoc status = %d\n", status);
    return (status);
}

int	ft_count_redir(t_token *token)
{
	int		i;
	t_token	*curr;
	
	i = 0;
	if (!token)
		return (0);
	curr = token;
	while (curr && (ft_cop(curr->s) != 1))
	{
		if (ft_cop(curr->s) > 1)
		{
			if (curr->next)
				i++;
		}
		if (curr)
			curr = curr->next;
	}
	return (i);
}

int	ft_redir_out(t_token *token, int fd[], int *i_fd)
{
	char *temp;

	temp = ft_get_subtoken(token->next->s);
	fd[*i_fd] = open(token->next->s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 126));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("minishell: error redirecting stdout\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_in(t_token *token, int fd[], int *i_fd)
{
	char *temp;

	temp = ft_get_subtoken(token->next->s);
	fd[*i_fd] = open(token->next->s, O_RDONLY);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 126));
	if (dup2(fd[*i_fd], STDIN_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdin\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_redir_append(t_token *token, int fd[], int *i_fd)
{
	char	*temp;
	int		status;
	
	temp = ft_get_subtoken(token->next->s);
	status = ft_get_path_aux(token->next->s);
	if (status != 0)
		return (status);
	fd[*i_fd] = open(token->next->s, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(temp);
	if (fd[*i_fd] == -1)
		return (ft_perror("minshell: Permission denied\n", 126));
	if (dup2(fd[*i_fd], STDOUT_FILENO) == -1)
		return (ft_perror("dup2: redirecting stdout\n", 1));
	(*i_fd)++;
	return (0);
}

int	ft_mod_fd(t_main_vars *mv, t_token *token, int fd[], int *i_fd)
{
	int	cop;

	cop = ft_cop(token->s);
	if (cop == 2)
		return (ft_redir_out(token, fd, i_fd));
	else if (cop == 3)
		return (ft_redir_in(token, fd, i_fd));
	else if (cop == 4)
	        return (ft_redir_append(token, fd, i_fd));
	else if (cop == 5)
		return (ft_heredoc(mv, token, fd, i_fd));
	return (0);
}

int	ft_bckp_fd(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(STDERR_FILENO);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
		return (ft_perror("minishell: redirect: bckup fd\n", 1));
	}
	return (0);
}

void	ft_close_fd(int fd[], int i_fd)
{
	int j;

	j = 3;
	while(j < i_fd)
	{
		close(fd[j]);
		j++;
	}
}

void	ft_restore_fd(int fd[])
{
	if (!fd)
		return ;
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int	ft_get_redir(t_main_vars *mv, t_token *head, int **fd, int *count)
{
	int		r;
	int		i_fd;
	t_token	*token;

	token = head;
	*count = ft_count_redir(token);
	if (*count == 0)
		return (0);
	else 
		*count += 3;
	i_fd = 3;
	while(token)
	{
		r = ft_mod_fd(mv, token, *fd, &i_fd);
		if (r)
			return (r);
		token = token->next;
	}
	ft_close_fd(*fd, i_fd);
	return (0);
}
