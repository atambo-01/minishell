/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:02:46 by eneto             #+#    #+#             */
/*   Updated: 2025/01/21 14:29:54 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 1. se n tiver args, ex: "export" apenas imprimir em orfdem alfabetica
// 2. dividir o nome do valor da variavel de ambiente
// 3. se tiver args, percorrer cada um dos nomes e checkar se o nome da variavel tem algum char n permitido 
// 4. aloca memoria pra nova matrix com tamanho + 1 e depois copia o que já estava lá e acrescenta a nova rl_variable_value
char    *ft_export(char **args, t_list **env)
{
    int i;
    int j;
    char **new_env;
    char *name;
    char *value;

    i = 0;
    while (args[i])
    {
        j = 0;
        while (args[i][j] && args[i][j] != '=')
        {
            if(!ft_isalnum(args[i][j]) && args[i][j] != '_')
            {
                ft_putstr_fd("minishell: export: `", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
                return (NULL);
            j++;
        }
        if (args[i][j] == '=')
        {
            name = ft_substr(args[i], 0, j);
            value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
            if (ft_is_valid_name(name))
            {
                ft_add_env(name, value, env);
            }
            else
            {
                ft_putstr_fd("minishell: export: `", 2);
                ft_putstr_fd(name, 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
            }
            free(name);
            free(value);
        }
        else
        {
            ft_add_env(args[i], "", env);
        }
        i++;
    }
    return (NULL);
}
}
