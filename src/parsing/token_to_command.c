#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

int	count_words(t_token_word *word)
{
	int count = 0;
	while (word)
	{
		count++;
		word = word->next;
	}
	return count;
}

// 🔧 Convertit t_token_word* en tableau de char**
char	*join_token_words(t_token_word *word)
{
	size_t	len = 0;
	t_token_word *tmp = word;

	// 1. Calcule la longueur totale sans espaces
	while (tmp)
	{
		len += strlen(tmp->word);
		tmp = tmp->next;
	}

	char *result = malloc(len + 1);
	if (!result)
		return NULL;
	result[0] = '\0';

	// 2. Concatène sans ajouter d’espace
	tmp = word;
	while (tmp)
	{
		strcat(result, tmp->word);
		tmp = tmp->next;
	}

	return result;
}


// 🔧 Ajoute une redirection à la liste
t_redirection *add_redirection(t_redirection **redir_list, t_token_type type, t_token_word *word)
{
	t_redirection *new = malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = strdup(word->word);
	new->fd = -1;
	new->next = NULL;

	if (!*redir_list)
		*redir_list = new;
	else
	{
		t_redirection *last = *redir_list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

// 🔧 Ajoute une string à un tableau de char**
char	**append_arg(char **args, t_token_word *word)
{
	int		old_size = 0;
	char	**new_args;
	char	*joined;

	if (!word)
		return args;

	while (args && args[old_size])
		old_size++;

	new_args = malloc(sizeof(char *) * (old_size + 2));
	if (!new_args)
		return NULL;

	// Copie les anciens args
	for (int i = 0; i < old_size; i++)
		new_args[i] = args[i];

	joined = join_token_words(word); // <- cette version sans espaces
	new_args[old_size] = joined;
	new_args[old_size + 1] = NULL;

	free(args);
	return new_args;
}

// 🎯 Fonction principale : transforme t_token* en t_commande*
t_commande	*convert_tokens_to_command(t_token *tokens)
{
	t_commande	*cmd_head = NULL;
	t_commande	*cmd_curr = NULL;

	while (tokens)
	{
		// Nouvelle commande au début ou après un pipe
		if (!cmd_curr)
		{
			cmd_curr = malloc(sizeof(t_commande));
			if (!cmd_curr)
				return (NULL);
			cmd_curr->args = NULL;
			cmd_curr->redirection = NULL;
			cmd_curr->next = NULL;

			// Ajoute à la liste chaînée
			if (!cmd_head)
				cmd_head = cmd_curr;
			else
			{
				t_commande *last = cmd_head;
				while (last->next)
					last = last->next;
				last->next = cmd_curr;
			}
		}

		if (tokens->type == TOK_WORD)
		{
			cmd_curr->args = append_arg(cmd_curr->args, tokens->word);
		}
		else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_REDIR_OUT ||
				tokens->type == TOK_REDIR_APPEND || tokens->type == TOK_HEREDOC)
		{
			if (tokens->next && tokens->next->type == TOK_WORD)
			{
				add_redirection(&cmd_curr->redirection, tokens->type, tokens->next->word);
				tokens = tokens->next; // skip the file token
			}
			else
			{
				fprintf(stderr, "Unexpected missing redirection target\n");
				return NULL;
			}
		}
		else if (tokens->type == TOK_PIPE)
		{
			cmd_curr = NULL; // next loop will allocate new t_commande
		}

		tokens = tokens->next;
	}
	return cmd_head;
}