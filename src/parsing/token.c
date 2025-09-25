/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:53:16 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:22:07 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_node_operator(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = operator(word);
	new->word = NULL;
	new->next = NULL;
	return (new);
}

static void	add_back(t_token **token, t_token *new)
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

t_token	*create_tok(char *word, t_shell_ctx *ctx, char **res, t_token **token)
{
	t_token_word	*new_word;
	t_token			*new;

	if (word[0] == '<' || word[0] == '>' || word[0] == '|')
		new = new_node_operator(word);
	else
	{
		new_word = split_node_word(word, ctx);
		if (!new_word)
		{
			handle_token_error(res, token);
			return (NULL);
		}
		new = new_node(new_word);
	}
	if (!new)
	{
		handle_token_error(res, token);
		return (NULL);
	}
	return (new);
}

int	tokenize_line(t_token **token, char *str, t_shell_ctx *ctx)
{
	char	**res;
	int		i;
	t_token	*new;

	res = ft_split_token(str);
	if (!res)
		return (1);
	i = 0;
	while (res[i])
	{
		new = create_tok(res[i], ctx, res, token);
		if (!new)
			return (1);
		add_back(token, new);
		i++;
	}
	free_split(res);
	return (0);
}