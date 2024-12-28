#include "../inc/minishell.h"

char	*ft_cutstr(char *str, char c, unsigned int inc)
{
	char	*res;
	char	*start;
	char	*end;
	int		i;

	i = 0;
	start = NULL;
	end = NULL;
	start = ft_strchr(str, c);
	while(start && *(start + 1) == c) start++;
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

int	ft_count_tokens_2(char *line, unsigned int *i, unsigned int *k)
{
	char *curr = &line[*k];
	
	if (*k == 0)
	{
		(*i)++;
		if (ft_strchr(line, ' '))
		{
			(*k) = (unsigned int)(ft_strchr(line, ' ') - line);
			return(1);
		}
	}
	else if (*curr == ' ' && *(curr + 1) != ' ')
	{ 
		if (ft_strchr(curr + 1, ' '))
		{
			(*i)++;
			(*k) = (unsigned int)(ft_strchr(curr + 1, ' ') - line);
			return(1);
		}
		if (ft_strchr(curr + 1, '\0'))
		{
			(*i)++;
			(*k) = (unsigned int)(ft_strchr(curr + 1, '\0') - line);
			return(1);
		}
	} 
	return(0);
}

unsigned int	ft_count_tokens(char *line)
{
	unsigned int	i;
	unsigned int	k;
	char		flag;	

	k = 0;
	i = 0;
	flag = '"';
	if (!line || !*line)
		return (i);
	while(line[k] == ' ')
		line++;
	while(line[k])
	{
		if (line[k] == flag && line[k + 1] != (flag || 0) && line[k + 2]) 
		{	
			if (ft_strchr(&line[k + 2], flag))
			{
				i++;
				k = (unsigned int)(ft_strchr(&line[k + 2], flag) - &line[k]) + 1;
			}	
		}
		else if (line[k] == flag && line[k + 1] == flag)
			k = k + 2;
		else if (flag == '"')
			flag = '\'';
		else if (ft_count_tokens_2(line, &i, &k))
		{
			
		}
		else
		{
			flag = '"';
			k++;
		}
		printf("k = %d\n", k);
		if (!ft_count_tokens_2(line, &i, &k))
			k++;
	}
	return(i);
}

/*
char	**ft_get_tokens(char *line)
{
	char	**words;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (!line || !*line)
		return (NULL);
	words = malloc(sizeof(char **));
	while(line[k] == ' ' || '\t')
		line++;
	while(line[k])
	{
		if (line[k] == '"' && ft_strchr(&line[k + 1], '"'))
		{		
			words[i] = ft_cutstr(&line[k], '"', 0);
			k = ft_strlen(words[i] + 2);
			i++;
		}
		else if (line[k] == '\'' && ft_strchr(&line[k + 1], '\''))
		{
			words[i] = ft_cutstr(&line[k], '\'', 0);
			k = ft_strlen(words[i] + 2);
			i++;	
		}
		else if (line[k] == ' ' && k == 0)
		{
			words[i] = malloc(sizeof(char *) * (ft_strchr(&line[k], ' ') - line + 1));
			while(line[k] && line[k] != ' ')
			{
				words[i][j] = line[k];
				j++;
				k++;
			}
			words[i][j] = 0;
			i++;
		}
		else if (line[k] == ' ' && ft_strchr(&line[k + 1], ' '))
		{
			words[i] = ft_cutstr(&line[k], ' ', 0);
			k = ft_strlen(words[i] + 2);
			i++;
		}
	}
	words[i] == NULL;
	return(words);
}
*/
