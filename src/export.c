/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:07 by eneto             #+#    #+#             */
/*   Updated: 2025/03/03 11:01:34 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_valid_name(char *name)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		f = 1;
	else
	{
		while (name[i] && name[i] != '=' && f == 0)
		{
			if (!ft_isalnum(name[i]) && name[i] != '_')
				f = 2;
			i++;
		}
	}
	if (f != 0)
	{
		ft_perror("minishell: export: ", 2);
		ft_perror(name, 2);
		ft_perror(": not a valid identifier\n", 2);
		return (f);
	}
	return (0);
}

int	ft_print_ex(t_env **env)
{
	t_env	*temp;

	temp = (*env)->next;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **envp)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!args[1])
		return (ft_print_ex(envp));
	else
	{
		while (args[i])
		{
			tmp = ft_strchr(args[i], '=');
			if (tmp == NULL && ft_is_valid_name(args[i]) == 0)
			{
				if (ft_getenv(*envp, args[i]) == NULL)
					ft_add_env_node(*envp, args[i]);
			}
			else if (ft_is_valid_name(args[i]) == 0)
				ft_add_env_node(*envp, args[i]);
			i++;
		}
	}
	return (0);
}
