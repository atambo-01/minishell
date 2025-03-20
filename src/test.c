/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:00:26 by eneto             #+#    #+#             */
/*   Updated: 2025/03/20 12:00:58 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**ft_token_to_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		size;
	int		i;
	char	*tmp_str;

	tmp = env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	envp = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp_str = ft_strjoin(env->name, "=");
			envp[i] = ft_strjoin(tmp_str, env->value);
			free(tmp_str);
		}
		else
			envp[i] = ft_strdup(env->name);
		if (!envp[i])
			return (NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}