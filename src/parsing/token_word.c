/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:24:43 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:20:43 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	fill_expandable(t_token_word *token)
{
	char	*str;

	if (token->word[0] == '\'')
		token->expendable = 0;
	if (token->word[0] == '\'' || token->word[0] == '\"')
	{
		str = delete_quote(token->word);
		if (!str)
			return (1);
		free(token->word);
		token->word = str;
	}
	return (0);
}

static int	add_word_to_list(t_token_word **head, char *str, t_shell_ctx *ctx)
{
	t_token_word	*new;

	new = new_node_word(str);
	if (!new)
		return (1);
	if (fill_expandable(new))
		return (1);
	if (expand_token_word(new, ctx))
		return (1);
	add_back_word(head, new);
	return (0);
}

t_token_word	*split_node_word(char *str, t_shell_ctx *ctx)
{
	char			**word;
	int				i;
	t_token_word	*head;

	head = NULL;
	word = ft_split_word(str);
	if (!word)
		return (NULL);
	i = 0;
	while (word[i])
	{
		if (add_word_to_list(&head, word[i], ctx))
		{
			free_split(word);
			free_token_words(head);
			return (NULL);
		}
		i++;
	}
	free(word);
	return (head);
}