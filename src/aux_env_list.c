/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:15:47 by eneto             #+#    #+#             */
/*   Updated: 2025/02/22 23:39:17 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_get_env(t_env *env, const char *name)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env   *ft_envp_to_list(char **envp)
{
    t_env   *head;
    t_env   *new_node;
    t_env   *current;
    int     i;

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
        if (!head)
        {
            head = new_node;
            current = head;  // Initialize current
        }
        else
        {
            current->next = new_node;
            current = new_node;  // Move current forward
        }
        i++;
    }
    return (head);
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
	envp = (char **)malloc(sizeof(char *) * (size + 1));
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
