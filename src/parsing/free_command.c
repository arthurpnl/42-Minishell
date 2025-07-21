#include "minishell.h"

// Libère un tableau de char**
void	free_args(char **args)
{
	if (!args)
		return;
	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

// Libère la liste des redirections
void	free_redirection(t_redirection *redir)
{
	t_redirection *tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

// Libère la liste des commandes
void	free_commande(t_commande *cmd)
{
	t_commande *tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_args(tmp->args);
		free_redirection(tmp->redirection);
		free(tmp);
	}
}

// Affiche une redirection
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

// Affiche une commande complète
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