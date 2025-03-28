/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:15:47 by eneto             #+#    #+#             */
/*   Updated: 2025/03/21 10:37:15 by eneto            ###   ########.fr       */
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

t_env	*ft_envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		new_node = ft_create_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		ft_aux(&head, &new_node, &current);
		i++;
	}
	return (head);
}

int	get_env_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**ft_token_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	char	*tmp_str;

	envp = (char **)ft_malloc(sizeof(char *) * (get_env_size(env) + 1));
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
