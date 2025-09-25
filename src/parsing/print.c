/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:47:25 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:16:15 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *token)
{
	while (token)
	{
		printf("Token type: %d\n", token->type);
		t_token_word *word = token->word;
		while (word)
		{
			printf("  Word: [%s] (expendable: %d)\n", word->word, word->expendable);
			word = word->next;
		}
		token = token->next;
	}
}

void	print_redirection(t_redirection *redir)
{
	while (redir)
	{
		printf("  Redirection: ");
		if (redir->type == TOK_REDIR_IN)
			printf("< ");
		else if (redir->type == TOK_REDIR_OUT)
			printf("> ");
		else if (redir->type == TOK_REDIR_APPEND)
			printf(">> ");
		else if (redir->type == TOK_HEREDOC)
			printf("<< ");
		else
			printf("? ");

		printf("%s\n", redir->file);
		redir = redir->next;
	}
}

void	print_commande(t_commande *cmd_list)
{
	int index = 0;

	while (cmd_list)
	{
		printf("=== Commande %d ===\n", index++);

		if (cmd_list->args)
		{
			printf("  Args: ");
			for (int i = 0; cmd_list->args[i]; i++)
				printf("[%s] ", cmd_list->args[i]);
			printf("\n");
		}
		else
			printf("  Args: (none)\n");

		if (cmd_list->redirection)
			print_redirection(cmd_list->redirection);
		else
			printf("  Redirection: (none)\n");

		cmd_list = cmd_list->next;
	}
}