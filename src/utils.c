/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:22 by atambo            #+#    #+#             */
/*   Updated: 2025/03/21 10:34:28 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

void	free_on_add_env_node(char *name, char *value)
{
	free(name);
	free(value);
}

int	ft_cop(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|')
		return (1);
	else if (str[0] == '>' && str[1] == '>')
		return (4);
	else if (str[0] == '<' && str[1] == '<')
		return (5);
	else if (str[0] == '>')
		return (2);
	else if (str[0] == '<')
		return (3);
	else
		return (0);
}

int	ft_cop_syntax(char *line)
{
	int	i;
	int	cop;

	i = 0;
	cop = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		cop = ft_cop(&line[i]);
		if (cop >= 4)
			i++;
		if (cop && (!line[i + 1] || ft_cop(&line[i + 1])))
			return (ft_perror("error: bad control operator syntax\n", 2));
		if (cop && line[i + 1] == ' ')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (!line[i] || ft_cop(&line[i]))
				return (ft_perror("error: bad control operator syntax\n", 2));
		}
		i++;
	}
	return (0);
}
	//	if (line[i] == 0 || line[i + 1] == 0)
	//		return(1);	//	if (line[i] == 0 || line[i + 1] == 0)
	//		return(1);
