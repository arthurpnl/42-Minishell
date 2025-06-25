#include "minishell.h"

void	tokenize_line(t_token **token, char *line)
{
	int		i;
	int		quote;
	t_token	*new;

	quote = 0;
	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			if (line[i] == '\"' || line[i] == '\'')
				quote = 2;
			new = new_node(ft_strdup_word(&line[i], &quote));
			if (!new)
				exit(1);
			add_node(token, new);
			i += ft_lenword(&line[i], &quote);
		}
	}
}

int ft_lenword(char *str, int *quote)
{
	int i = 0;
	if (!*quote)
	{
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			i++;
	}
	else
	{
		i++;
		while (str[i] != '\"' && str[i] != '\'' && str[i])
			i++;
		i++;
		(*quote)--;
	}
	return i;
}

char *ft_strdup_word(char *str, int *quote)
{
	int i = 0;
	char *dest;
	int	len;

	len = ft_lenword(str, quote);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return NULL;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

t_token	*new_node(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = word;
	new->type = 0;
	new->quote = 0;
	new->next = NULL;
	return (new);
}

void	add_node(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}