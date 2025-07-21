/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:00:10 by mehdi             #+#    #+#             */
/*   Updated: 2025/07/12 11:12:14 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_REDIR_APPEND || type == TOK_HEREDOC);
}

int	is_word(t_token *token)
{
	return (token && token->type == TOK_WORD && token->word != NULL);
}

int	check_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*last;

	curr = tokens;
	last = tokens;
	if (!curr)
		return (0);
	if (curr->type == TOK_PIPE)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (curr)
	{
		if (curr->type == TOK_PIPE)
		{
			if (!curr->next)
			{
				fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			if (curr->next->type == TOK_PIPE)
			{
				fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			if (is_redirection(curr->next->type))
			{
				fprintf(stderr, "minishell: syntax error near unexpected token `<' or `>' after `|'\n");
				return (1);
			}
		}
		else if (is_redirection(curr->type))
		{
			if (!curr->next)
			{
				fprintf(stderr, "minishell: syntax error: unexpected end after redirection\n");
				return (1);
			}
			if (curr->next->type != TOK_WORD)
			{
				fprintf(stderr, "minishell: syntax error near unexpected token ");
				if (curr->next->type == TOK_PIPE)
					fprintf(stderr, "`|'\n");
				else
					fprintf(stderr, "`<' or `>'\n");
				return (1);
			}
		}
		else if (curr->type == TOK_HEREDOC)
		{
			if (!curr->next || curr->next->type != TOK_WORD)
			{
				fprintf(stderr, "minishell: syntax error: heredoc requires a delimiter\n");
				return (1);
			}
		}
		curr = curr->next;
	}
	while (last->next)
		last = last->next;
	if (last->type == TOK_PIPE)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}