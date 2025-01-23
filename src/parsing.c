/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:20:04 by atambo            #+#    #+#             */
/*   Updated: 2025/01/23 17:21:13 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_gt2_a1(char *old, char *new, t_count **p_c)
{
	t_count	*c;

	c = *p_c;
	if (old[c->i] == c->q && ft_strchr(old + c->i + 1, c->q))
	{
		while (old[c->i + 1] != c->q)
		{
			//	if (q == '"' && (old == '$' || old[k] == '\\') )
			//	ft_expand(old + i, new);
			new[(c->k)] = old[(c->i) + 1];
			(c->k)++;
			(c->i)++;
		}
		c->i += 1;
	}
	else if (c->q == '"')
		c->q = '\'';
	else
	{
		new[(c->k)] = old[(c->i)];
		c->q = '"';
		(c->k)++;
		(c->i)++;
	}
}

char	*ft_get_token_2(char *old, t_count *c)
{
	char	*new;

	c = ft_counter();
	c->q = '"';
	new = ft_malloc(sizeof(char) * ft_strlen(old) + 1);
	while (old[c->i])
		ft_gt2_a1(old, new, &c);
	free(old);
	old = NULL;
	return (new);
}

void	ft_process_quotes(char ch, t_count *c)
{
    if (ch == '"' && c->q == 0)
        c->q = 1;
    else if (ch == '"' && c->q == 1)
        c->q = 0;
    if (ch == '\'' && c->q == 0)
        c->q = 2;
    else if (ch == '\'' && c->q == 2)
        c->q = 0;
}

void	ft_handle_pipe(char *line, t_list **token, t_count *c)
{
    if (c->k >= 1 && line[c->k - 1] != ' ')
    {
        c->temp = c->k - c->last + 1;
        add_token(line, token, &c);
    }
    add_pipe(token);
    skip_spaces(line, &c);
    c->last = c->k + 1;
}

void	ft_handle_space_or_end(char *line, t_list **token, t_count *c)
{
    c->end = (line[c->k + 1] == 0);
    c->temp = c->k + c->end - c->last + 1;
    add_token(line, token, &c);
    skip_spaces(line, &c);
    c->last = c->k;
}

void	ft_get_token_if(char *line, t_list **token, t_count *c)
{
	printf("line[c->k] = _%s_\n", &line[c->k]);
    if (c->q == 0 && line[c->k] == '|')
	{
        (ft_handle_pipe(line, token, c));
	}
    else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
    {
		(ft_handle_space_or_end(line, token, c));
	}    
}

t_list *ft_get_token(char *line)
{
	t_count *c;
	t_list 	*token;
	
	token = NULL;
	c = ft_counter();
	char *trimmed = ft_strtrim(line, " ");
	line = trimmed;
	while (line[c->k])
	{
		ft_get_token_if(line, &token, c);
		(c->k)++;
		/* 
		   ft_process_quotes(line[c->k], c);
		 */
	}
	if (c->q != 0)
		printf("error: unclosed quotes\n");
	ft_free_p((void **)&(trimmed));
	ft_free_p((void **)&c);
	line = NULL;
	return (token);
}

