/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:20:04 by atambo            #+#    #+#             */
/*   Updated: 2025/01/21 11:36:50 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
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

t_list	*ft_get_token_if(char *line, t_list **p_token, t_count **p_c)
{
	t_count	*c;
	t_list	*token;

	c = *p_c;
	token = *p_token;
	if (c->q == 0 && line[c->k] == '|')
	{
		if (c->k - 1 >= 0 && line[c->k - 1] != ' ')
		{
			c->temp = c->k - c->last + 1;
			token = add_token(line, &token, &c);
		}
		token = add_pipe(&token);
		skip_spaces(line, &c);
		c->last = c->k;
	}
	else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
	{
		c->aux = (line[c->k + 1] == 0);
		c->temp = c->k + c->aux - c->last + 1;
		token = add_token(line, &token, &c);
		skip_spaces(line, &c);
		c->last = c->k;
	}
	return (token);
}

t_list	*ft_get_token(char *line)
{
	t_count	*c;
	t_list	*head;
	t_list	*token;
	char	*ptr;

	token = NULL;
	token = ft_malloc(sizeof(t_list));
	c = ft_counter();
	head = token;
	ptr = line;
	line = ft_strtrim(line, " ");
	free(ptr);
	ptr = NULL;
	while (line[c->k])
	{
		token = ft_get_token_if(line, &token, &c);
		if (line[c->k] == '"' && c->q == 0)
			c->q = 1;
		else if (line[c->k] == '"' && c->q == 1)
			c->q = 0;
		if (line[c->k] == '\'' && c->q == 0)
			c->q = 2;
		else if (line[c->k] == '\'' && c->q == 2)
			c->q = 0;
		(c->k)++;
	}
	if (c->q != 0)
		printf("error. unclosed quotes\n");
	free(line);
	line = NULL;
	return (head);
}
*/

void ft_process_quotes(char ch, t_count *c)
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

t_list *ft_handle_pipe(char *line, t_list *token, t_count *c)
{
    if (c->k - 1 >= 0 && line[c->k - 1] != ' ')
    {
        c->temp = c->k - c->last + 1;
        token = add_token(line, &token, &c);
    }
    token = add_pipe(&token);
    skip_spaces(line, &c);
    c->last = c->k;
    return (token);
}

t_list *ft_handle_space_or_end(char *line, t_list *token, t_count *c)
{
    c->aux = (line[c->k + 1] == 0);
    c->temp = c->k + c->aux - c->last + 1;
    token = add_token(line, &token, &c);
    skip_spaces(line, &c);
    c->last = c->k;
    return (token);
}

t_list *ft_get_token_if(char *line, t_list *token, t_count *c)
{
    if (c->q == 0 && line[c->k] == '|')
        return (ft_handle_pipe(line, token, c));
    else if ((c->q == 0 && line[c->k] == ' ') || line[c->k + 1] == 0)
        return (ft_handle_space_or_end(line, token, c));
    return (token);
}

t_list *ft_get_token(char *line)
{
    t_count *c = ft_counter();
    t_list *head = NULL;
    t_list *token = ft_malloc(sizeof(t_list));
    char *trimmed = ft_strtrim(line, " ");

    free(line);
    line = trimmed;
    head = token;
    while (line[c->k])
    {
        token = ft_get_token_if(line, token, c);
        ft_process_quotes(line[c->k], c);
        (c->k)++;
    }
    if (c->q != 0)
        printf("error: unclosed quotes\n");
    free(line);
    return (head);
}

