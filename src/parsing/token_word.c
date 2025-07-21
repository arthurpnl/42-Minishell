#include "minishell.h"

t_token_word	*split_node_word(char *str, char **env)
{
	char			**word;
	int				i;
	t_token_word	*head_word;
	t_token_word	*new_word;

	head_word = NULL;
	i = 0;
	word = ft_split_word(str);
	if (!word)
		return (NULL);
	while (word[i])
	{
		new_word = new_node_word(word[i]);
		if (!new_word)
			exit(1);
		fill_expandable(new_word);
		expand(new_word, env);
		// printf("expanddddddd %s\n", new_word->word);
		add_back_word(&head_word, new_word);
		i++;
	}
	// free_split(word);
	return (head_word);
}

t_token_word	*new_node_word(char *str)
{
	t_token_word	*new;

	new = malloc(sizeof(t_token_word));
	if (!new)
		return (NULL);
	new->word = str;
	new->expendable = 1;
	new->next = NULL;
	return (new);
}

t_token	*new_node(t_token_word *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = TOK_WORD;
	new->word = word;
	new->next = NULL;
	return (new);
}

void	fill_expandable(t_token_word *token)
{
	char	*str;

	if (token->word[0] == '\'')
		token->expendable = 0;
	if (token->word[0] == '\'' || token->word[0] == '\"')
	{
		str = delete_quote(token->word);
		free(token->word);
		token->word = str;
	}
}

char	*delete_quote(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 1;
	j = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!line)
		return (NULL);
	while (str[i+1])
		line[j++] = str[i++];
	line[j] = '\0';
	return (line);
}