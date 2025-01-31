/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:02:13 by eneto             #+#    #+#             */
/*   Updated: 2025/01/30 13:05:54 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_var_wq(const char *var)
{
	char	*s;

	s = ft_strchr(var, '=');
	if (s)
		printf("=\"%s\"\n", s + 1);
	else
		printf("\n");
}

void	print_ex(char **env)
{
	int	i;

	i = 0;
	if (!env || !(*env)[i])
		return ;
	while (env[i] != NULL)
	{
		printf("declare - x %s", env[i]);
		if (ft_strchr(env[i], '='))
			print_var_wq(env[i]);
		else
			printf("\n");
		i++;
	}
}
