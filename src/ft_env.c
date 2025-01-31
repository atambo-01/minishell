/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:00:39 by eneto             #+#    #+#             */
/*   Updated: 2025/01/30 12:41:27 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_cmd *env)
{
	int	i;
	int	count;

	/*env->path = getenv("PATH");
	if (env->path == NULL)
	{
		ft_putendl_fd("Erro: env: No such file or directory", 2);
		return ;
	}*/
	count = 0;
	while (env->params && env->params[count])
		count++;
	i = 0;
	if (count == 0)
	{
		while (env->ft_envp && env->ft_envp[i])
			printf("%s\n", env->ft_envp[i++]);
	}
	else
		ft_putendl_fd("Erro: env: too many arguments", 2);
}
