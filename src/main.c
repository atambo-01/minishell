/*                                                                            */
/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:09:36 by eneto             #+#    #+#             */
/*   Updated: 2025/01/09 14:10:26 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int		ft_list_size(t_list *head)
{
	int	i;

	i = 0;
	if (!head)
		return(0);
	while(head->next)
	{
		i++;
		head = head->next;
	}
	return(i);
}

void	ft_token_ls(t_list *token)
{
	if (!token)
		return;
	int  i = 0;
	while(token)
	{
		if (token && token->s)
			printf("%s", token->s);
		token = token->next;
		if (token && token->s)
			printf("->");
	}
	printf("\n");
	return;
}
/*
int main(int ac, char **av)
{
	if (ac > 1)
	{
		int i = 3;
		printf("%s\n----------------------\n", av[1]);
		t_list *token = ft_get_token(av[1]);
		ft_token_ls(token);		
		printf("%d tokens\n", ft_list_size(token));
		ft_token_ls(token);
		ft_get_token_2(&(token));
	}
	return (0);
}
*/
int	main(void)
{
	char	*line;
	t_list	*token;
	while(1)
	{	
		line = readline("minishell>");
		printf("%s\n", line);
		token = ft_get_token(line);
		ft_token_ls(token);
		add_history(line);
	}
}
