/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:41:49 by atambo            #+#    #+#             */
/*   Updated: 2025/03/10 14:03:45 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_get_env_value(char *var_name, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name, var_name) == 0)
			return (ft_strdup(env->value));
        env = env->next;
    }
	return (NULL);
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
	 	if ((line[i] == '"' || line[i] == '\'') && q == 0)
            q = line[i];
        else if ((line[i] == '"' || line[i] == '\'') && q == line[i])
            q = 0;
		i++;
	}
	if (q != 0)
		return(ft_perror("minishell: error, unclosed quotes\n", 2));
	return(0);
}

void	ft_exp_exit(char **exp_line, t_count *c, int p_exit)
{
	char	*exit;
	char 	*temp;

	exit = ft_itoa(p_exit);
	temp = ft_strjoin(*exp_line, exit);
	free(*exp_line);
	*exp_line = temp;
	c->k += ft_strlen(exit);
	c->i += 1;
	free(exit);
}

char	*ft_exp_env(t_count *c, char *line,  char **exp_line, t_env *env)
{
	char    *v_name;
	char	*v_value;
	char	*temp;

	temp = NULL;
	v_value = NULL;
	c->start = c->i + 1;
	c->end = c->start;
	while (ft_isalnum(line[c->end]) || line[c->end] == '_')
		(c->end)++;
	v_name = ft_malloc(sizeof(char) * (c->end - c->start + 1));
	if (!v_name)
	{
		return (NULL);
	}
	strncpy(v_name, &line[c->start], c->end - c->start);
	v_name[c->end - c->start] = '\0';
	v_value = ft_get_env_value(v_name, env);
	if (v_value && *v_value)
	{
		temp = ft_strjoin(*exp_line, v_value);
		*exp_line = NULL;
	}
	c->k += strlen(&(*exp_line[c->k]));
	free(v_name);
	free(v_value);
	c->i = c->end - 1;
	if (temp)
		return(temp);
	return(NULL);
}


char	*ft_expand(char *line, t_env *env, const int p_exit, int s_quote)
{
	t_count		c;
    char    	*exp_line;
	char		*temp;
	
	ft_counter(&c);
    if (!line || !env)
        return (NULL);
    exp_line = ft_calloc(sizeof(char) , strlen(line));
    if (!exp_line)
        return (NULL);
    while (line[c.i])
    {
        if ((line[c.i] == '"' || line[c.i] == '\'') && c.q == 0)
            c.q = line[c.i];
        else if ((line[c.i] == '"' || line[c.i] == '\'') && c.q == line[c.i])
            c.q = 0;
        if (c.q == 0 && line[c.i] == ' ')
        {
            if (c.k > 0 && exp_line[c.k - 1] != ' ')
                exp_line[(c.k)++] = ' ';
            while (line[c.i + 1] == ' ')
                (c.i)++;
        }
		else if ((c.q != '\'' || s_quote) && line[c.i] == '$' &&
			 line[c.i + 1] == '?')
		{
			ft_exp_exit(&exp_line, &c, p_exit);
     	}
		else if ((c.q != '\'' || s_quote) && line[c.i] == '$' &&
			 ft_isalpha(line[c.i + 1]))
		{
			temp = ft_exp_env(&c, line, &exp_line, env);
			if (temp)
			{
				free(exp_line);
				exp_line = temp;
			}
		}
		else
		{
           exp_line[(c.k)++] = line[c.i];
		}
        (c.i)++;
    }
    exp_line[c.k] = '\0';
	return(exp_line);
}
