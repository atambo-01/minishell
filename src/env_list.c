/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:08:23 by eneto             #+#    #+#             */
/*   Updated: 2025/02/23 14:13:34 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_init_env_values(t_env *node, char *env)
{
	char	*equal;
	char	*msg;

	msg = "aqui\0";
	equal = ft_strchr(env, '=');
	if (equal)
	{
		node->name = ft_substr(env, 0, equal - env);
		node->value = ft_strdup(equal + 1);
	}
	else
	{
		node->name = ft_strdup(env);
		node->value = NULL;
	}
	if (!node->name || (equal && !node->value))
	{
		free(node->name);
		free(node->value);
		free(node);
		return (0);
	}
	return (1);
}

t_env	*ft_create_env_node(const char *env)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!ft_init_env_values(node, (char *)env))
		return (NULL);
	node->next = NULL;
	return (node);
}

void	ft_add_env_node(t_env *env, char *str)
{
	t_env	*new_node;
	char	*name;
	char	*value;

	if (!env || !str)
		return ;
	if (ft_strchr(str, '=') == NULL)
	{
		name = ft_strdup(str);
		value = NULL;
	}
	else
	{
		name = ft_substr(str, 0, ft_strchr(str, '=') - str);
		value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (env->value != NULL)
				free(env->value);
			env->value = value;
			return ;
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	new_node = ft_create_env_node_2(name, value);
	if (!new_node)
		return ;
	free(name);
	free(value);
	env->next = new_node;
}

void	ft_free_env(t_env **p_env)
{
	t_env	*env;
	t_env	*next;

	if (!p_env || !*p_env || !(*p_env)->name)
		return ;
	env = *p_env;
	while (env)
	{
		next = env->next;
		free(env->name);
		free(env->value);
		env->name = NULL;
		env->value = NULL;
		free(env);
		env = NULL;
		env = next;
	}
}
