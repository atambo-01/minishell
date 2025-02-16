/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:55:21 by eneto             #+#    #+#             */
/*   Updated: 2025/02/16 16:14:04 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_env **env, char **params)
{
	int	i;

	i = 0;
	if (!env || !*env || !params)
		return (0);
	while (params[++i])
	{
		if (ft_get_env(*env, params[i]))
			ft_remove_env_node(env, params[i]);
	}
	return (0);
}
