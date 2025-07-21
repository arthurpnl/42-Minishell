#include "minishell.h"

void	tokenize_line(t_token **token, char *str, char **env)
{
	char			**res;
	int				i;
	t_token			*new;
	t_token_word	*new_word;

	i = 0;
	res = ft_split(str);
	int j = 0;
	if (!res)
		exit(1);
	while (res[i])
	{
		if (res[i][0] == '<' || res[i][0] == '>' || res[i][0] == '|')
			new = new_node_operator(res[i]);
		else
		{
			new_word = split_node_word(res[i], env);
			new = new_node(new_word);
		}
		if (!new)
			exit(1);
		add_back(token, new);
		i++;
	}
}

// t_token	*new_node_word(char *word)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->type = TOK_WORD;
// 	new->word.word = NULL;
// 	new->word.expendable = 0;
// 	new->word.next = NULL;
// 	new->next = NULL;
// 	return (new);
// }

t_token	*new_node_operator(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = operator(word);
	new->word = NULL;
	// new->word.expendable = 0;
	// new->word.next = NULL;
	new->next = NULL;
	return (new);
}

int	operator(char *word)
{
	if (word[0] == '<' && !word[1])
		return (TOK_REDIR_IN);
	else if (word[0] == '>' && !word[1])
		return (TOK_REDIR_OUT);
	else if (word[0] == '|' && !word[1])
		return (TOK_PIPE);
	else if (word[0] == '<' && word[1] == '<')
		return (TOK_HEREDOC);
	else if (word[0] == '>' && word[1] == '>')
		return (TOK_REDIR_APPEND);
	return (-1);
}

void	add_back(t_token **token, t_token *new)
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

void	add_back_word(t_token_word **token, t_token_word *new)
{
	t_token_word	*tmp;

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

void	free_split(char **tab)
{
	int i = 0;

	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}