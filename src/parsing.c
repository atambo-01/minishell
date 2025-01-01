#include "../inc/minishell.h"

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
			printf("HERE_1\n");
			while(old[i + 1] != q)
			{
				/*
				if (q == '"' && (old == '$' || old[k] == '\\') )
				{
					ft_expand(old + i, new);
				}
				*/
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

t_list	*ft_get_token(char *line)
{
	t_list	*token;
	t_list	*head;
	int		last;
	int		k;
	int		aux;
	int		q;

	q == 0;
	aux = 0;
	last = 0;
	k = 0;
	token = malloc(sizeof(t_list *));
	head = token;
	while(*line == ' ')
		line++;
	while(line[k])
	{
		if (q == 0 && (line[k] == ' ' || line[k + 1] == 0))
		{
			if (line[k + 1] == 0)
				aux = 1;
			token->s = malloc(sizeof(char*) * (k + aux - last + 1));
			ft_strlcpy(token->s, &line[last], k + aux - last + 1);
			token->next = malloc(sizeof(t_list*));
			token = token->next;
			token->next = NULL;
			while(line[k + 1] == ' ')
				k++;
			last = k + 1;}
		if		(line[k] == '"' && q == 0)
			q = 1;
		else if (line[k] == '"' && q == 1)
			q = 0;
		if		(line[k] == '\'' && q == 0)
			q = 2;
		else if (line[k] == '\'' && q == 2 )
			q = 0;
		k++;
	}
	if (k == 0)
	{
		free(head);
		head = NULL;
	}
	return(head);
}













