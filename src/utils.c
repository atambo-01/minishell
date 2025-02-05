/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:22 by atambo            #+#    #+#             */
/*   Updated: 2025/02/05 02:39:05 by atambo           ###   ########.fr       */
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
		return (2);
	else if (str[0] == '<' && str[1] == '<')
		return (3);
	else if (str[0] == '>')
		return (4);
	else if (str[0] == '<')
		return (5);
	else
		return (0);
}

int	ft_ctrl_syntax(char *trim)
{
	int	i;
	int	cop;
	
	i = 1;
	cop = 0;
	if (!trim)
		return (0);
	if (!ft_ctrl_operator(trim))
	{
		while(trim[i])
		{
			cop = ft_ctrl_operator(&trim[i]);
			if (cop && !trim[i + 1])
				break;	
			if (cop  && trim[i + 1])
			{
				while(trim[i] == ' ')
					i++;
				if (ft_ctrl_operator(&trim[i + 1]))
					break;
			}
			if (trim[i + 1] == 0)
				return(1);
			i++;
		}
	}
	free(trim);
	printf("error: bad control operator syntax.\n");
	return(0);
}
