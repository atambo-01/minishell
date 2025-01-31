/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:02:46 by eneto             #+#    #+#             */
/*   Updated: 2025/01/30 16:26:13 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_envrealloc(char **env, char *new_env)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (!env || !*env || !**env || !new_env)
		return (NULL);
	while (env[i])
		i++;
	new_envp = (char **)ft_calloc(sizeof(char *), (i + 2));
	if (new_envp == NULL)
		return (NULL);
	i = -1;
	while (env[++i] != NULL)
		new_envp[i] = ft_strdup(env[i]);
	new_envp[i] = ft_strdup(new_env);
	free(new_env);
	ft_free_p((void **)env);
	return (new_envp);
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
int ft_mtxlen(char **mtx)
{
	int	i;
	
	i = 0;
	if(mtx == NULL || mtx[0] == NULL)
		return(0);
	while(mtx[i])
		i++;
	return(i);
}
void	ft_add_env(char *name, char *value, char ***env)
{
	int		i;
	char	*new_env;
	char	*temp;
	char	**mtx;

	i = 0;
	if (value == NULL && ft_vfy_name(name, env))
		return ;
	mtx = malloc(sizeof(char *) * (ft_mtxlen((*env)) + 2));
	while ((*env)[i])
	{
		mtx[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	temp = ft_strjoin(name, "=");
	new_env = ft_strjoin(temp, value);
	free(temp);
	mtx[i] = new_env;
	mtx[i + 1] = NULL;
	*env = mtx;
	// ft_envrealloc(env, new_env);
}

int	ft_is_valid_name(char *name)
{
	int	i;
	int	f;

	i = 0;
	f = -1;
	if (ft_isdigit(name[0]) == 1)
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
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

// 1. se n tiver args, ex: "export" apenas imprimir em orfdem alfabetica
// 2. dividir o nome do valor da variavel de ambiente
// 3. se tiver args,
// percorrer cada um dos nomes e checkar se o nome da variavel tem algum char n permitido
// 4. aloca memoria pra nova matrix com tamanhoif (!ft_is_valid_name(args[i]))
void	ft_export(char **args, char ***env)
{
	int		i;
	char	*name;
	char	*value;
	char	*tmp;

	i = -1;
	if (!args)
	{
		print_ex(*env);
		return ;
	}
	while (args[++i])
	{
		tmp = ft_strchr(args[i], '=');
		if (!tmp)
		{
			if (!ft_is_valid_name(args[i]))
				continue ;
			ft_add_env(args[i], NULL, env);
		}
		else
		{
			name = ft_substr(args[i], 0, (tmp - args[i]));
			value = ft_substr(args[i], tmp - args[i] + 1, ft_strlen(tmp + 1));
			ft_add_env(name, value, env);
			free(name);
			free(value);
		}
	}
}
