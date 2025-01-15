/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:31:03 by eneto             #+#    #+#             */
/*   Updated: 2025/01/11 17:03:56 by eneto            ###   ########.fr       */
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
