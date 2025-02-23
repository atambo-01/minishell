/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:41:49 by atambo            #+#    #+#             */
/*   Updated: 2025/02/23 01:21:22 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_get_env_value(char *var_name, char *dest, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, var_name) == 0 && env->value != NULL)
        {
        	ft_strcpy(dest, env->value);
			return;
        }
        env = env->next;
    }
}

int	ft_check_quotes(char *line)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	if (!line)
		return (0);
	while(line[i])
	{
		if (line[i] == '"' && q == 0)
			q = 1;
		else if (line[i] == '"' && q == 1)
			q = 0;
		if (line[i] == '\'' && q == 0)
			q = 2;
		else if (line[i] == '\'' && q == 2)
			q = 0;
		i++;
	}
	if (q != 0)
		printf("error: unclosed quotes\n");
	return(q);
}

char	*ft_expand(char *line, t_env *env, const int prev_exit)
{
    int     i = 0, q = 0, start, end, x = 0;
    char    *exp_line;
    char    *var_name;
	
    if (!line || !env)
        return (NULL);
    exp_line = ft_malloc(1024);
    if (!exp_line)
        return (NULL);
    while (line[i])
    {
        if (line[i] == '"' && q == 0)
            q = 1;
        else if (line[i] == '"' && q == 1)
            q = 0;
        if (line[i] == '\'' && q == 0)
            q = 2;
        else if (line[i] == '\'' && q == 2)
            q = 0;
        if (q == 0 && line[i] == ' ')
        {
            if (x > 0 && exp_line[x - 1] != ' ')
                exp_line[x++] = ' ';
            while (line[i + 1] == ' ')
                i++;
        }
		else if (q != 2 && line[i] == '$' && line[i + 1] == '?')
		{
			char	*exit;		
			exit = ft_itoa(prev_exit);
			ft_strlcpy(&(exp_line[x]), exit, ft_strlen(exit) + 1);
			x += ft_strlen(exit);
			i += 1;
			free(exit);
		}
     	else if (q != 2 && line[i] == '$' && ft_isalpha(line[i + 1]))
        {
            start = i + 1;
            end = start;
            while (ft_isalnum(line[end]) || line[end] == '_')
                end++;
            var_name = ft_malloc(sizeof(char) * (end - start + 1));
            if (!var_name)
            {
                free(exp_line);
                return (NULL);
            }
            strncpy(var_name, &line[start], end - start);
            var_name[end - start] = '\0';
            ft_get_env_value(var_name, &exp_line[x], env);
            x += strlen(&exp_line[x]);  // Move x forward
            free(var_name);
            i = end - 1;  // Move past the variable
		}
		else
            exp_line[x++] = line[i];
        i++;
    }
    exp_line[x] = '\0';
	return(exp_line);
}


