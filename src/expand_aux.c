/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:59:44 by atambo            #+#    #+#             */
/*   Updated: 2025/03/22 20:26:57 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_env_value(char *var_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, var_name) == 0 && env->value != NULL)
			return (ft_strdup(env->value));
		else if (ft_strcmp(env->name, var_name) == 0)
			return (ft_strdup(""));
		env = env->next;
	}
	return (ft_strdup(""));
}

int	ft_check_quotes(char *line)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && q == 0)
			q = line[i];
		else if ((line[i] == '"' || line[i] == '\'') && q == line[i])
			q = 0;
		i++;
	}
	if (q != 0)
		return (ft_perror("minishell: error, unclosed quotes\n", 2));
	return (0);
}

void	ft_exp_exit(char **exp_line, t_count *c, int p_exit)
{
	char	*exit;
	char	*temp;

	exit = ft_itoa(p_exit);
	temp = ft_strjoin(*exp_line, exit);
	free(*exp_line);
	*exp_line = temp;
	c->k += ft_strlen(exit);
	c->i += 1;
	free(exit);
}

char	*ft_exp_env(t_count *c, char *line, char **exp_line, t_env *env)
{
	char	*v_name;
	char	*v_value;
	char	*temp;

	c->start = c->i + 1;
	c->end = c->start;
	while (ft_isalnum(line[c->end]) || line[c->end] == '_')
		c->end++;
	v_name = ft_malloc(sizeof(char) * (c->end - c->start + 1));
	if (!v_name)
		return (NULL);
	strncpy(v_name, &line[c->start], c->end - c->start);
	v_name[c->end - c->start] = '\0';
	v_value = ft_get_env_value(v_name, env);
	temp = ft_strjoin(*exp_line, v_value);
	free(*exp_line);
	*exp_line = temp;
	c->k += ft_strlen(v_value);
	c->i = c->end - 1;
	free(v_name);
	free(v_value);
	return (temp);
}
