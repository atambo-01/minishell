/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:07 by eneto             #+#    #+#             */
/*   Updated: 2025/02/27 17:32:00 by atambo           ###   ########.fr       */
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
		ft_putstr_fd("minishell> export: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (f);
	}
	return (0);
}

void	ft_print_ex(t_env **env)
{
	int		i;
	t_env	*temp;

	i = 1;
	temp = (*env)->next;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
}

int	ft_export(char **args, t_env **envp)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!args[1])
	{
		ft_print_ex(envp);
		return (0);
	}
	else
	{
		while (args[i])
		{
			tmp = ft_strchr(args[i], '=');
			if (!tmp)
			{
				if (!ft_is_valid_name(args[i]))
					ft_add_env_node(*envp, args[i]);
			}
			else if (!ft_is_valid_name(args[i]))
				ft_add_env_node(*envp, args[i]);
			i++;
		}
	}
	return (0);
}
