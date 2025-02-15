/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:15:07 by eneto             #+#    #+#             */
/*   Updated: 2025/02/12 19:32:37 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	**ft_envrealloc(char **env, char *new_env)
// {
// 	int		i;
// 	char	**new_envp;

// 	i = 0;
// 	if (!env || !*env || !**env || !new_env)
// 		return (NULL);
// 	while (env[i])
// 		i++;
// 	new_envp = (char **)ft_calloc(sizeof(char *), (i + 2));
// 	if (new_envp == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (env[++i] != NULL)
// 		new_envp[i] = ft_strdup(env[i]);
// 	new_envp[i] = ft_strdup(new_env);
// 	free(new_env);
// 	ft_free_p((void **)env);
// 	return (new_envp);
// }
void	print_ex(char **env)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = NULL;
	if (!env || !(*env))
		return ;
	while (env[i] != NULL)
	{
		tmp = ft_strchr(env[i], '=');
		if (tmp)
			printf("declare -x %.*s=\"%s\"\n", (int)(tmp - env[i]), env[i], tmp
				+ 1);
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}
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
		//free((*env)[i]);
		i++;
	}
	if (value == "")
		value = "";
	else if (!(ft_strchr(value, ' ')))
		value = "";
	temp = ft_strjoin(name, "=");
	new_env = ft_strjoin(temp, value);
	//free(temp);
	mtx[i] = new_env;
	mtx[i + 1] = NULL;
	*env = mtx;
}

// 1. se n tiver args, ex: "export" apenas imprimir em orfdem alfabetica
// 2. dividir o nome do valor da variavel de ambiente
// 3. se tiver args,
// percorrer cada um dos nomes e checkar se o nome da variavel tem algum char n permitido
// 4. aloca memoria pra nova matrix com tamanhoif (!ft_is_valid_name(args[i]))

/*
void	ft_export(char **args, char ***env)
{
	int i;
	char *name;
	char *value;
	char *tmp;

	i = 0;
	if (!args || !args[0])
	{
		print_ex(*env);
		return ;
	}
	else
	{
		while (args[i])
		{
			tmp = ft_strchr(args[i], '=');
			if (!tmp)
			{
				if (ft_is_valid_name(args[i]))
					ft_add_env(args[i], NULL, env);
			}
			else if (ft_is_valid_name(args[i]))
			{
				name = ft_substr(args[i], 0, (tmp - args[i]));
				value = ft_substr(args[i], tmp - args[i] + 1, ft_strlen(tmp + 1));
				printf("name: %s_ \nvalue: %s_\n", name, value);
				ft_add_env(name, value, env);
				free(name);
				free(value);
			}
			i++;
		}
	}
	return;
}
*/


