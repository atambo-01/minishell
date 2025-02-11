#include "../inc/minishell.h"

t_env	*ft_create_env_node(const char *env)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = ft_malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env, '=');
	if (equal_sign)
	{
		new_node->name = ft_substr(env, 0, equal_sign - env);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_node->name = ft_strdup(env);
		new_node->value = NULL;
	}
	if (!new_node->name || (equal_sign && !new_node->value))
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_remove_env_node(t_env **head, const char *name)
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
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_add_env_node(t_env **head, const char *env)
{
	t_env	*new_node;
	t_env	*current;

	if (!head || !env)
		return;
	current = *head;
	while (current)
	{
		if (ft_strcmp(current->name, env) == 0)
		{
			free(current->value);
			current->value = ft_strdup(ft_strchr(env, '=') + 1);
			return;
		}
		if (!current->next)
			break;
		current = current->next;
	}
	new_node = ft_create_env_node(env);
	if (!new_node)
		return;
	if (!current)
		*head = new_node;
	else
		current->next = new_node;
}

t_env	*ft_envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*current;
	int		i;

	head = NULL;
	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		new_node = ft_create_env_node(envp[i++]);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
		{
			current = head;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
	}
	return (head);
}

void	ft_free_env(t_env **p_env)
{
	t_env	*env;
	t_env	*next;

	if (!p_env || !*p_env || !(*p_env)->name)
		return;
	env = *p_env;
	while(env)
	{
		next = env->next;
		free(env->name);
		free(emv->value);
		env->name = NULL;
		env->valuew = NULL;
		free(env);
		env = NULL;
		env = next;
	}
}

