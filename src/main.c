/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: eneto <eliandrasibo12@gmail.com>           +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/12/19 18:09:36 by eneto             #+#    #+#             */
/*   Updated: 2025/01/06 10:24:00 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = (readline("minishell$"));
		add_history(prompt);
	}
	return (0);
}
