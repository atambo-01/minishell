/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:22 by atambo            #+#    #+#             */
/*   Updated: 2025/01/24 14:47:12 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	ft_ctrl_operator(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "|"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, "<<"))
		return (3);
	else if (!ft_strcmp(str, ">"))
		return (5);
	else if (!ft_strcmp(str, "<"))
		return (6);
	else
		return (0);
}

