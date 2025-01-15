/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/12/19 19:24:37 by eneto             #+#    #+#             */
/*   Updated: 2024/12/19 19:24:37 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_pipe
{
	int fd[2];
	pid_t pid;
	const char *c0;
	const char *c1;
} t_pipe;

int	pipes(t_pipe *command);
void	echo(char *phrase);
void	verifyp(t_pipe *command);

#endif