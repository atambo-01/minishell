/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:09:36 by eneto             #+#    #+#             */
/*   Updated: 2024/12/19 18:09:36 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

void	ft_token_ls(t_list *token)
{
	if (!token)
		return;
	while(token)
	{
		printf("%s->", token->s);
		token = token->next;
	}
	return;
}

int main(int ac, char **av)
{
	if (ac > 1)
	{
	char	*line;
	t_list	*token;

	//	line = readline("minishell> ");
	//	add_history(line);
		token = ft_get_token(av[1]);
		ft_token_ls(token);
		free(token);
	}
	return (0);
}
