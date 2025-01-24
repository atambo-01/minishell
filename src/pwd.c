/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:35:20 by atambo            #+#    #+#             */
/*   Updated: 2025/01/24 10:48:41 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char	*buff;

	buff = ft_malloc(PATH_MAX);
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	ft_free_p((void **)&buff);
}
