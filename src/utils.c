/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:22 by atambo            #+#    #+#             */
/*   Updated: 2025/02/07 01:45:54 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	ft_ctrl_operator(char *str)
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

int	ft_ctrl_syntax(char *line)
{
	int	i;
	int	cop;
	
	i = 1;
	cop = 0;
	if (!line)
		return (0);
	if (!ft_ctrl_operator(line))
	{
		while(line[i])
		{
			cop = ft_ctrl_operator(&line[i]);
			if (cop >= 4)
				i++;
			if (cop && (!line[i + 1] || ft_ctrl_operator(&line[i + 1])))
				break;	
			if (cop  && line[i + 1] == ' ')
			{
				i++;
				while(line[i] == ' ')
					i++;
				if (ft_ctrl_operator(&line[i]))
					break;
			}
			if (line[i + 1] == 0)
				return(1);
			i++;
		}
	}
	free(line);
	printf("error: bad control operator syntax.\n");
	return(0);
}



