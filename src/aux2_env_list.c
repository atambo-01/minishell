/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:21:43 by eneto             #+#    #+#             */
/*   Updated: 2025/02/21 18:03:36 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_list_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s", env->name);
		if (env->value != NULL)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
}

t_env	*ft_create_env_node_2(char *name, char *value)
{
	t_env	*new_node;

	if (!name)
		return (NULL);
	new_node = ft_malloc(sizeof(t_env));
	new_node->name = ft_strdup(name);
	new_node->value = NULL;
	if (value)
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	ft_remove_env_node(t_env **head, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
