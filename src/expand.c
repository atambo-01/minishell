/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <atambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:41:49 by atambo            #+#    #+#             */
/*   Updated: 2025/03/13 14:01:33 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_init_exp(t_count *c, char **exp_line, size_t len)
{
	ft_counter(c);
	*exp_line = ft_calloc(sizeof(char), len + 1024);
}

static void	ft_handle_space(char *line, t_count *c, char *exp_line)
{
	if (c->k > 0 && exp_line[c->k - 1] != ' ')
		exp_line[c->k++] = ' ';
	while (line[c->i + 1] == ' ')
		c->i++;
}

static void	ft_handle_quote(char *line, t_count *c)
{
	if (c->q == 0)
		c->q = line[c->i];
	else if (c->q == line[c->i])
		c->q = 0;
}

static char	*ft_process_exp(char *line, t_count *c, char **exp_line, t_data *d)
{
	char	*temp;

	if ((c->q != '\'' || d->s_quote) && line[c->i] == '$'
		&& line[c->i + 1] == '?')
		ft_exp_exit(exp_line, c, d->p_exit);
	else if ((c->q != '\'' || d->s_quote) && line[c->i] == '$'
		&& ft_isalpha(line[c->i + 1]))
	{
		temp = ft_exp_env(c, line, exp_line, d->env);
		if (!temp)
		{
			free(*exp_line);
			return (NULL);
		}
	}
	else
		(*exp_line)[c->k++] = line[c->i];
	return (*exp_line);
}

char	*ft_expand(char *line, t_env *env, const int p_exit, int s_quote)
{
	t_count	c;
	char	*exp_line;
	t_data	d;

	if (!line || !env)
		return (NULL);
	d.env = env;
	d.p_exit = p_exit;
	d.s_quote = s_quote;
	ft_init_exp(&c, &exp_line, strlen(line));
	if (!exp_line)
		return (NULL);
	while (line[c.i])
	{
		ft_handle_quote(line, &c);
		if (c.q == 0 && line[c.i] == ' ')
			ft_handle_space(line, &c, exp_line);
		else if (!ft_process_exp(line, &c, &exp_line, &d))
			return (NULL);
		c.i++;
	}
	exp_line[c.k] = '\0';
	return (exp_line);
}
