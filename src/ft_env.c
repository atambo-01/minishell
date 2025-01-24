/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:00:39 by eneto             #+#    #+#             */
/*   Updated: 2025/01/24 16:11:23 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	ft_env(t_cmd *env)
{
	int			i;
	int			count;
	extern char	**environ;

	i = 0;
	count = 0;
	env->path = getenv("PATH");
	if (env->path == NULL)
	{
		ft_putstr_fd("Erro: env: No such file or directory", 2);
		return ;
	}
	while (env->ft_envp[count])
		count++;
	if (count == 1)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
	else
		printf("Erro: env: too many arguments\n");
}
