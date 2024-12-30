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
	if (inc = -1)
		start = str;
	else
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
	printf("ft_cutstr sucess\n");
	return(res);
}

t_list	*ft_get_token(char *line)
{
	char			flag;
	t_list			*start;	
	t_list			*token;
	unsigned int	k;
	int  i; //debuging del afterwards

	k = 0;
	i = 0; //here
	if (!line || !*line)
			return (start);
	token = malloc(sizeof(t_list*));
	start = token;
	flag = '"';
	while(line[k] == ' ')
		line++;
	while(line[k])
	{
		printf("k = %d\n%s\n", k, &line[k]);
		printf("flag = %c\n", flag);
		if (line[k] == flag)
				printf("here\n");
		if (line[k] == flag && line[k + 1] != flag && 
			ft_strchr(&line[k + 1], flag))
		{
			token->s = ft_cutstr(&line[k], flag, 0);
			token->next = malloc(sizeof(t_list*));
			token = token->next;
			token->next = NULL;
			k += (unsigned int)(ft_strchr(&line[k + 1], flag) - &line[k]) + 1;
			i++;
		}
		else if (line[k] == flag && line[k + 1] == flag)
		{
			printf("skip 2\n");
			k = k + 2;
		}
		else if (flag == '"')
		{
			flag = '\'';
		}	
		else if (k == 0 && ft_strchr(line, ' '))
		{
			token->s = ft_cutstr(line, ' ', -1);
			token->next = malloc(sizeof(t_list*));
			token = token->next;
			token->next = NULL;
			k += (unsigned int)(ft_strchr(line, ' ') - line);
			i++;//here
			printf("first space\n");
		}	
		else
		{
			flag = '"';
			k++;
		}
		printf("token = %d\n--------------\n", i);
	}
	return(start);
}



/*	else if (line[k] == ' ' && line[k + 1] != ' ')
	{ 
	if (ft_strchr(&line[k + 1], ' '))
	{
	token = malloc(sizeof(t_list*));
	token->s = ft_cutstr(&line[k + 1], ' ', 0);
	token = token->next;
	token->next = NULL;
	k = (unsigned int)(ft_strchr(&line[k + 1], ' ') - line);
	}
	if (ft_strchr(&line[k + 1], '\0'))
	{
	token = malloc(sizeof(t_list*));
	token->s = ft_cutstr(&line[k + 1], 0, 0);
	token = token->next;
	token->next = NULL;
	k = (unsigned int)(ft_strchr(&line[k + 1], 0) - line);
	}
	}	*/










