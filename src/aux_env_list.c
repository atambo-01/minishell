/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:15:47 by eneto             #+#    #+#             */
/*   Updated: 2025/03/20 12:35:42 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_getenv(t_env *env, const char *name)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (env->value)
				return (env->value);
			else
				return ("no name or =");
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_aux(t_env **head, t_env **new, t_env **cur)
{
	if (!(*head))
	{
		*head = *new;
		*cur = *head;
	}
	else
	{
		(*cur)->next = *new;
		*cur = *new;
	}
}

char	**ft_token_to_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		size;
	int		i;
	char	*tmp_str;

	tmp = env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	envp = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp_str = ft_strjoin(env->name, "=");
			envp[i] = ft_strjoin(tmp_str, env->value);
			free(tmp_str);
		}
		else
			envp[i] = ft_strdup(env->name);
		if (!envp[i])
			return (NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
