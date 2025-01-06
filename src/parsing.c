/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atambo <alex.tambo.15432@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:20:04 by atambo            #+#    #+#             */
/*   Updated: 2025/01/06 23:35:13 by atambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
char	*ft_cutstr(char *str, char c, int inc)
{
	char	*res;
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = NULL;
	end = NULL;
	if (inc == -1)
		start = str;
	else
	{
		start = ft_strchr(str, c);
		while(start && *(start + 1) == c)
			start++;
	}		
	if (start)
		end = ft_strchr(start + 2, c);
	if (!str || !*str || !start || !end || end - start < 1 )
		return(NULL);
	if (inc == 0)
	{
		start++;
		end--;
	}
	if (start == end)
		res = malloc(sizeof(char*) * 2);
	else
		res = malloc(sizeof(char*) * (end - start + 1));
	while(end >= start + i)
	{
		res[i] = start[i];
		i++;
	}
	res[i] = 0;
	return(res);
}


char	*ft_get_token_2(char **p_old)
{
	int		i;
	int		k;
	char	*new;
	char	*old;
	char	q;
	
	i = 0;
	k = 0;
	q = '"';
	old = *p_old;
	new = malloc(sizeof(char *) * ft_strlen(old) + 1);
	while(old[i])
	{
		if (old[i] == q && ft_strchr(old + i + 1, q))
		{
			while(old[i + 1] != q)
			{
				if (q == '"' && (old == '$' || old[k] == '\\') )
				{
					ft_expand(old + i, new);
				}
				new[k] = old[i + 1];
				k++;
				i++;
			}
			i += 2;;
		}
		else if (q == '"')
			q = '\'';
		else
		{
			new[k] = old[i];
			k++;
			q = '"';
			i++;
		}
	}
	free(old);
	old = NULL;
	return(new);
}
*/

t_count	*ft_counter(void)
{
	t_count	*c;

	c = malloc(sizeof(t_count));
	c->i = 0;
	c->j = 0;
	c->k = 0;
	c->last = 0;
	c->q = 0;
	c->temp = 0;
	c->aux = 0;
	return (c);
}

t_list	*add_token(char *line, t_list **p_token, t_count **p_c)
{
	t_list	*token;
	t_list	*res;
	t_count	*c;

	token = *p_token;
	c = *p_c;
	token->s = malloc(sizeof(char *) * (c->temp));
	ft_strlcpy(token->s, &line[c->last], c->temp);
	token->next = malloc(sizeof(t_list *));
	token = token->next;
	token->next = NULL;
	return (token);
}

t_list	*add_pipe(t_list **p_token)
{
	t_list	*token;

	token = *p_token;
	token->s = malloc(sizeof(char *) * 2);
	token->s = "|";
	token->next = malloc(sizeof(t_list *));
	token = token->next;
	token->next = NULL;
	return (token);
}

void	skip_spaces(char *line, t_count **p_c)
{
	t_count	*c;

	c = *p_c;
	while (line[c->k] == ' ')
		(c->k)++;
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
		c->last = c->k + 1;
	}
	return (token);
}

t_list	*ft_get_token(char *line)
{
	t_count	*c;
	t_list	*head;
	t_list	*token;

	token = malloc(sizeof(t_list));
	c = ft_counter();
	head = token;
	line = ft_strtrim(line, " ");
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
	return (head);
}
