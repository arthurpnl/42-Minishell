#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_AND,
	TOK_OR,
	TOK_SEMICOLON,
	TOK_VAR
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	t_quote_type	quote;
	struct s_token	*next;
}	t_token;

void	sig_handler(int sig);

void	tokenize_line(t_token **token, char *line);
int ft_lenword(char *str, int *quote);
char *ft_strdup_word(char *str, int *quote);
t_token	*new_node(char *word);
void	add_node(t_token **token, t_token *new);
void	ft_free_token(t_token **stack);

void	print(t_token *stack);
char	*read_line_with_quotes(void);
int	is_quote_closed(char *str, char quote_char);

#endif