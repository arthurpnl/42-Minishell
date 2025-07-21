#include "minishell.h"

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *clean_space(char *str)
{
	char    *res;
	char	quote;
	int     i;
	int     j;

	j = 0;
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) * 3 + 1));
	if (!res)
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (!str[i])
				break ;
			res[j++] = ' ';
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			res[j++] = str[i];
			quote = str[i++];
			while (str[i] != quote)
			{
				res[j++] = str[i];
				i++;
			}
			res[j++] = str[i];
			i++;
		}
		else if (is_double_operator(&str[i]))
		{
			if (j != 0 && res[j-1] != ' ')
				res[j++] = ' ';
			res[j++] = str[i];
			res[j++] = str[i];
			i += 2;
			if (str[i] && str[i] != ' ' && !is_operator(str[i]))
				res[j++] = ' ';
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (j != 0 && res[j-1] != ' ')
				res[j++] = ' ';
			res[j++] = str[i];
			i++;
			if (str[i] && str[i] != ' ' && !is_operator(str[i]))
				res[j++] = ' ';
		}
		else
		{
			res[j++] = str[i];
			i++;
		}
	}
	res[j] = '\0';
	return res;
}

int is_double_operator(char *str)
{
	return ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'));
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}


// int main(int ac, char **av)
// {
//     char *test;

//     test = clean_space(av[1]);
//     printf("[%s]\n", test);
// 	free(test);

//     printf("%dY\n", len_clean_space(av[1]));
// }