/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:22 by atambo            #+#    #+#             */
/*   Updated: 2025/02/21 10:25:11 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	i = 1;
	cop = 0;
	if (!line)
		return (1);
	if (ft_cop(line) != 0)
		return (ft_perror("error: bad control operator syntax", 2));
	while (line[i])
	{
		cop = ft_cop(&line[i]);
		if (cop >= 4)
			i++;
		if (cop && (!line[i + 1] || ft_cop(&line[i + 1])))
		{
			return (ft_perror("error: bad control operator syntax", 3));
		}
		if (cop && line[i + 1] == ' ')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (!line[i] || ft_cop(&line[i]))
			{
				return (ft_perror("error: bad control operator syntax", 4));
			}
		}
		//	if (line[i] == 0 || line[i + 1] == 0)
		//		return(1);
		i++;
	}
	return (0);
}
