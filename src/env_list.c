#include "../inc/minishell.h"

t_env	*ft_get_env(t_env *env, const char *name)
{
	if (!env)
		return(NULL);
	while(env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return(env);
		env = env->next;
	}
	return(NULL);
}

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
		new_node->name = ft_strdup((char *)env);
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
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_add_env_node(t_env *env, char *str)
{
	t_env	*new_node;

	if (!env || !str)
		return;
	while (env->next)
	{
		if (ft_strncmp(env->name, str, ft_strlen(env->name)) == 0)
		{
			if (env->value != NULL)
				free(env->value);
			env->value = NULL;
			if (ft_strchr(str, '='))
				env->value = ft_strdup(ft_strchr(str, '=') + 1);
			return;
		}
		env = env->next;
	}
	new_node = ft_create_env_node(str);
	if (!new_node)
		return;
	env->next = new_node;
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

char    **ft_list_to_envp(t_env *env)
{
    char    **envp;
    t_env   *tmp;
    int     size;
    int     i;
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
		free(env->value);
		env->name = NULL;
		env->value = NULL;
		free(env);
		env = NULL;
		env = next;
	}
}

void	ft_list_env(t_env *env)
{
	if (!env)
		return ;
	while(env)
	{
		printf("%s", env->name);
		if (env->value != NULL)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
}
