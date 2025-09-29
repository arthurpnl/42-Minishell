/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 08:38:58 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/23 11:23:35 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Compte le nombre de mots dans une liste chaînée
int	count_words(t_token_word *word)
{
	int	count = 0;

	while (word)
	{
		count++;
		word = word->next;
	}
	return (count);
}

// Concatène une liste de t_token_word en une seule string
char	*join_token_words(t_token_word *word)
{
	size_t			len;
	t_token_word	*tmp;
	char			*res;

	len = 0;
	tmp = word;
	while (tmp)
	{
		len += strlen(tmp->word);
		tmp = tmp->next;
	}
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	tmp = word;
	while (tmp)
	{
		strcat(res, tmp->word);
		tmp = tmp->next;
	}
	return (res);
}

// Ajoute une redirection
t_redirection	*add_redirection(t_redirection **list,
	t_token_type type, t_token_word *word)
{
	t_redirection	*new;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = join_token_words(word);
	if (!new->file)
		return (free(new), NULL);
	new->fd = -1;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		t_redirection *last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

// Ajoute un argument concaténé au tableau args
char	**append_arg(char **args, t_token_word *word)
{
	int		old_size;
	char	**new_args;
	char	*joined;

	if (!word)
		return (args);
	old_size = 0;
	while (args && args[old_size])
		old_size++;
	new_args = malloc(sizeof(char *) * (old_size + 2));
	if (!new_args)
		return (NULL);
	for (int i = 0; i < old_size; i++)
		new_args[i] = args[i];
	joined = join_token_words(word);
	if (!joined)
		return (free(new_args), NULL);
	new_args[old_size] = joined;
	new_args[old_size + 1] = NULL;
	free(args);
	return (new_args);
}

// Convertit une liste de tokens en liste de commandes
t_commande	*tokens_to_command(t_token *tokens)
{
	t_commande	*head = NULL;
	t_commande	*curr = NULL;

	while (tokens)
	{
		if (!curr)
		{
			curr = calloc(1, sizeof(t_commande));
			if (!curr)
				return (NULL);
			if (!head)
				head = curr;
			else
			{
				t_commande *last = head;
				while (last->next)
					last = last->next;
				last->next = curr;
			}
		}
		if (tokens->type == TOK_WORD)
			curr->args = append_arg(curr->args, tokens->word);
		else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_REDIR_OUT
			|| tokens->type == TOK_REDIR_APPEND || tokens->type == TOK_HEREDOC)
		{
			if (tokens->next && tokens->next->type == TOK_WORD)
			{
				if (!add_redirection(&curr->redirection,
						tokens->type, tokens->next->word))
					return (NULL);
				tokens = tokens->next;
			}
			else
				return (fprintf(stderr,
					"minishell: missing redirection target\n"), NULL);
		}
		else if (tokens->type == TOK_PIPE)
			curr = NULL;
		tokens = tokens->next;
	}
	return (head);
}


// // Compte le nombre de mots dans une liste chaînée
// int	count_words(t_token_word *word)
// {
// 	int	count;

// 	count = 0;
// 	while (word)
// 	{
// 		count++;
// 		word = word->next;
// 	}
// 	return (count);
// }

// // Concatène une liste de t_token_word en une seule string
// char	*join_token_words(t_token_word *word)
// {
// 	size_t			len;
// 	t_token_word	*tmp;
// 	char			*res;

// 	len = 0;
// 	tmp = word;
// 	while (tmp)
// 	{
// 		len += ft_strlen(tmp->word);
// 		tmp = tmp->next;
// 	}
// 	res = malloc(len + 1);
// 	if (!res)
// 		return (NULL);
// 	res[0] = '\0';
// 	tmp = word;
// 	while (tmp)
// 	{
// 		strcat(res, tmp->word);
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }

// // Ajoute une redirection
// t_redirection	*add_redirection(t_redirection **list,
// 	t_token_type type, t_token_word *word)
// {
// 	t_redirection	*new;
// 	t_redirection	*last;

// 	last = NULL;
// 	new = malloc(sizeof(t_redirection));
// 	if (!new)
// 		return (NULL);
// 	new->type = type;
// 	new->file = join_token_words(word);
// 	if (!new->file)
// 		return (free(new), NULL);
// 	new->fd = -1;
// 	new->next = NULL;
// 	if (!*list)
// 		*list = new;
// 	else
// 	{
// 		last = *list;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new;
// 	}
// 	return (new);
// }

// // Ajoute un argument concaténé au tableau args
// char	**append_arg(char **args, t_token_word *word)
// {
// 	int		old_size;
// 	char	**new_args;
// 	char	*joined;
// 	int		i;

// 	if (!word)
// 		return (args);
// 	old_size = 0;
// 	while (args && args[old_size])
// 		old_size++;
// 	new_args = malloc(sizeof(char *) * (old_size + 2));
// 	if (!new_args)
// 		return (NULL);
// 	i = 0;
// 	while (i < old_size)
// 		new_args[i++] = args[i++];
// 	joined = join_token_words(word);
// 	if (!joined)
// 		return (free(new_args), NULL);
// 	new_args[old_size] = joined;
// 	new_args[old_size + 1] = NULL;
// 	free(args);
// 	return (new_args);
// }

// // 🔧 Alloue et ajoute une nouvelle commande à la liste
// static t_commande	*new_command_node(t_commande **head)
// {
// 	t_commande	*new;
// 	t_commande	*last;

// 	new = calloc(1, sizeof(t_commande));
// 	if (!new)
// 		return (NULL);
// 	if (!*head)
// 		*head = new;
// 	else
// 	{
// 		last = *head;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new;
// 	}
// 	return (new);
// }

// // 🔧 Gère les redirections
// static int	handle_redirection(t_commande *cmd, t_token **tokens)
// {
// 	if (!(*tokens)->next || (*tokens)->next->type != TOK_WORD)
// 	{
// 		fprintf(stderr, "minishell: missing redirection target\n");
// 		return (1);
// 	}
// 	if (!add_redirection(&cmd->redirection, (*tokens)->type,
// 			(*tokens)->next->word))
// 		return (1);
// 	*tokens = (*tokens)->next; // skip le mot du fichier
// 	return (0);
// }

// // 🎯 Transforme tokens → commandes
// t_commande	*tokens_to_command(t_token *tokens)
// {
// 	t_commande	*head;
// 	t_commande	*curr;

// 	head = NULL;
// 	curr = NULL;
// 	while (tokens)
// 	{
// 		if (!curr && !(curr = new_command_node(&head)))
// 			return (NULL);
// 		if (tokens->type == TOK_WORD)
// 			curr->args = append_arg(curr->args, tokens->word);
// 		else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_REDIR_OUT
// 			|| tokens->type == TOK_REDIR_APPEND || tokens->type == TOK_HEREDOC)
// 		{
// 			if (handle_redirection(curr, &tokens))
// 				return (free_commande(head), NULL);
// 		}
// 		else if (tokens->type == TOK_PIPE)
// 			curr = NULL;
// 		tokens = tokens->next;
// 	}
// 	return (head);
// }





// Convertit une liste de tokens en liste de commandes
// t_commande	*tokens_to_command(t_token *tokens)
// {
// 	t_commande	*head;
// 	t_commande	*curr;

// 	head = NULL;
// 	curr = NULL;
// 	while (tokens)
// 	{
// 		if (!curr)
// 		{
// 			curr = calloc(1, sizeof(t_commande));
// 			if (!curr)
// 				return (NULL);
// 			if (!head)
// 				head = curr;
// 			else
// 			{
// 				t_commande *last = head;
// 				while (last->next)
// 					last = last->next;
// 				last->next = curr;
// 			}
// 		}
// 		if (tokens->type == TOK_WORD)
// 			curr->args = append_arg(curr->args, tokens->word);
// 		else if (tokens->type == TOK_REDIR_IN || tokens->type == TOK_REDIR_OUT
// 			|| tokens->type == TOK_REDIR_APPEND || tokens->type == TOK_HEREDOC)
// 		{
// 			if (tokens->next && tokens->next->type == TOK_WORD)
// 			{
// 				if (!add_redirection(&curr->redirection,
// 						tokens->type, tokens->next->word))
// 					return (NULL);
// 				tokens = tokens->next;
// 			}
// 			else
// 				return (fprintf(stderr,
// 					"minishell: missing redirection target\n"), NULL);
// 		}
// 		else if (tokens->type == TOK_PIPE)
// 			curr = NULL;
// 		tokens = tokens->next;
// 	}
// 	return (head);
// }