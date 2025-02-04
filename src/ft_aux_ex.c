/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:18 by eneto             #+#    #+#             */
/*   Updated: 2025/02/03 14:52:06 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_mtxlen(char **mtx)
{
	int	i;

	i = 0;
	if (mtx == NULL || mtx[0] == NULL)
		return (0);
	while (mtx[i])
		i++;
	return (i);
}

int	ft_is_valid_name(char *name)
{
	int	i;
	int	f;

	i = 0;
	f = -1;
	if (ft_isdigit(name[0]))
		f = 0;
	else
	{
		while (name[i] != '\0')
		{
			if (!ft_isalnum(name[i]) && name[i] != '_')
				f = 0;
			i++;
		}
	}
	if (f == 0)
	{
		ft_putstr_fd("minishell> export: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}
int	ft_vfy_name(char *name, char ***env)
{
	char	*tmp;
	char	*mp;
	int		i;

	i = -1;
	while ((*env)[++i])
	{
		mp = ft_strchr((*env)[i], '=');
		if (!mp)
			tmp = ft_substr((*env)[i], 0, (mp - (*env)[i]));
		else
			tmp = ft_strdup((*env)[i]);
		if (!ft_strcmp(name, tmp))
		{
			free((*env)[i]);
			free(tmp);
			if (!mp)
				(*env)[i] = ft_strdup(name);
			else
				(*env)[i] = ft_strjoin(name, "=");
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}
