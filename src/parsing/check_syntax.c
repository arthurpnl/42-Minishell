/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:29:34 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:03:36 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_rules(t_token *curr)
{
	if (!curr->next || curr->next->type == TOK_PIPE
		|| is_redirection(curr->next->type))
		return (print_pipe_error());
	return (0);
}

static int	check_redir_rules(t_token *curr)
{
	if (!curr->next || curr->next->type != TOK_WORD)
		return (print_redir_error(curr->next));
	return (0);
}

static int	check_heredoc_rules(t_token *curr)
{
	if (!curr->next || curr->next->type != TOK_WORD)
		return (print_heredoc_error());
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (0);
	if (tokens->type == TOK_PIPE)
		return (print_pipe_error());
	curr = tokens;
	while (curr)
	{
		if (curr->type == TOK_PIPE && check_pipe_rules(curr))
			return (1);
		else if (is_redirection(curr->type) && check_redir_rules(curr))
			return (1);
		else if (curr->type == TOK_HEREDOC && check_heredoc_rules(curr))
			return (1);
		curr = curr->next;
	}
	if (tokens && tokens->next == NULL && tokens->type == TOK_PIPE)
		return (print_pipe_error());
	return (0);
}