/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:31:03 by eneto             #+#    #+#             */
/*   Updated: 2025/01/16 10:59:35 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(char *phrase)
{
	char	*ech;

	ech = "echo";
	while (phrase == ech)
		phrase++;
	if (phrase != ech)
	{
		printf("%s%s%s", " ", phrase, "\n");
	}
	return ;
}
int	ft_call_functions(char *function)
{
	if (function == "echo")
		ft_echo();
	else if (function == "cd")
		ft_cd();
	else if (function == "pwd")
		ft_pwd();
	else if (function == "export")
		ft_export();
	else if (function == "unset")
		ft_unset();
	else if (function == "env")
		ft_env();
	else if (function == "|")
		ft_pipe();
}
