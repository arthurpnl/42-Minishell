#include "minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}


int main(int ac, char **av)
{
	char	*input;
	t_token	*head;

	head = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// input = readline("minishell$ ");
		input = read_line_with_quotes();
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		tokenize_line(&head, input);
		print(head);
		ft_free_token(&head);
		free(input);
	}
	return (0);
}

void	print(t_token *stack)
{
	while (stack)
	{
		printf("word : %s\n", stack->token);
		stack = stack->next;
	}
}

void	ft_free_token(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp->token);
		free(tmp);
	}
	*stack = NULL;
}

int	is_quote_closed(char *str, char quote_char)
{
	int	i = 0;
	int	open = 0;

	while (str[i])
	{
		if (str[i] == quote_char)
			open = !open;
		i++;
	}
	return (!open);
}

char	*read_line_with_quotes(void)
{
	char	*line = NULL;
	char	*full_input = NULL;
	char	*tmp = NULL;

	line = readline("minishell$ ");
	if (!line)
		return (NULL);
	full_input = strdup(line);
	free(line);

	while (!is_quote_closed(full_input, '\'') || !is_quote_closed(full_input, '\"'))
	{
		line = readline("> ");
		if (!line)
			break;
		tmp = full_input;
		full_input = malloc(strlen(tmp) + strlen(line) + 2); // +1 pour \n ou espace
		if (!full_input)
			return (NULL);
		sprintf(full_input, "%s\n%s", tmp, line);
		free(tmp);
		free(line);
	}
	return (full_input);
}