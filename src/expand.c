/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:41:49 by atambo            #+#    #+#             */
/*   Updated: 2025/02/07 13:25:11 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void get_env_value(char *var_name, char *dest, char **ft_envp)
{
    int i = 0;
    int len = strlen(var_name);

    while (ft_envp[i])
    {
        if (strncmp(ft_envp[i], var_name, len) == 0 && ft_envp[i][len] == '=')
        {
            strcpy(dest, &ft_envp[i][len + 1]);  // Copy the value after '='
            return;
        }
        i++;
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

char	*ft_expand(char *line, char **ft_envp)
{
    int     i = 0, q = 0, start, end, x = 0;
    char    *exp_line;
    char    *var_name;
	
    if (!line || !ft_envp || !*ft_envp)
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

        // Handle spaces
        if (q == 0 && line[i] == ' ')
        {
            if (x > 0 && exp_line[x - 1] != ' ') // Only add space if the last char isn't already a space
                exp_line[x++] = ' ';
            while (line[i + 1] == ' ') // Skip consecutive spaces
                i++;
        }
        // Expand environment variables
     	else if (q != 2 && line[i] == '$' && ft_isalnum(line[i + 1]))
        {
            start = i + 1;
            end = start;
            while (ft_isalnum(line[end]) || line[end] == '_')
                end++;

            var_name = malloc(sizeof(char) * (end - start + 1));
            if (!var_name)
            {
                free(exp_line);
                return (NULL);
            }

            strncpy(var_name, &line[start], end - start);
            var_name[end - start] = '\0';

            get_env_value(var_name, &exp_line[x], ft_envp);

            x += strlen(&exp_line[x]);  // Move x forward
            free(var_name);
            i = end - 1;  // Move past the variable
		}
		else
        {
            exp_line[x++] = line[i];
        }
        i++;
    }
    exp_line[x] = '\0';
	return(exp_line);
}


