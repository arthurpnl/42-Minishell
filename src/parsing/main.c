/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/08/27 17:25:18 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void rl_replace_line(const char *text, int clear_undo);
void	sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*input;
	char	*str;
	t_token	*head;
	char	**cpy_env;

	cpy_env = ft_cpy_envp(envp);
	head = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (quote_not_closed(input))
			free(input);
		else
		{
			str = clean_space(input);
			//printf("%s\n", str);
			// char	**res = ft_split(str);
			// while (*res)
			// 	printf("(%s)\n", *res++);
			free(input);
			tokenize_line(&head, str, cpy_env);
			if (!check_syntax(head))
			{
				t_commande *commands = convert_tokens_to_command(head);

				if (commands)
				{
					print_commande(commands);
					command_dispatch(commands, cpy_env);
					// une fois terminé
					free_commande(commands);
				}
			}
			// print_tokens(head);
			ft_free_token(&head);
			free(str);
		}
	}
	return (0);
}

void	print(t_token *stack)
{
	while (stack)
	{
		printf("type : %d\n", stack->type);
		stack = stack->next;
	}
}

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


void	ft_free_token(t_token **token)
{
	t_token			*tmp;
	t_token_word	*tmp2;
	t_token_word	*word;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		word = tmp->word;
		while (word)
		{
			tmp2 = word;
			word = word->next;
			free(tmp2->word);
			free(tmp2);
		}
		free(tmp);
	}
	*token = NULL;
}