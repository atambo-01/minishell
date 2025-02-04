/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:00:39 by eneto             #+#    #+#             */
/*   Updated: 2025/02/03 10:51:34 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_cmd *env)
{
	int		i;
	int		count;
	char	*value;

	count = 0;
	while (env->params && env->params[count])
		count++;
	i = 0;
	if (count == 0)
	{
		while (env->ft_envp && env->ft_envp[i])
		{
			value = ft_strchr(env->ft_envp[i], '=');
			if (value && value[1] != '\0')
				printf("%s\n", env->ft_envp[i]);
			i++;
		}
	}
	else
		ft_putendl_fd("Erro: env: too many arguments", 2);
}
