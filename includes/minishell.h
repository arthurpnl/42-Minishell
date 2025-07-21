#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_token_type
{
	TOK_WORD,			// 0
	TOK_PIPE,			// | = 1
	TOK_REDIR_IN,		// < = 2
	TOK_REDIR_OUT,		// > = 3
	TOK_REDIR_APPEND,	// >> = 4
	TOK_HEREDOC			// << = 5
}	t_token_type;

typedef struct s_token_word
{
	char	*word;
	int		expendable;
	struct s_token_word	*next;
}	t_token_word;

typedef struct s_token
{
	t_token_word	*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	int						fd;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_commande
{
	char				**args;
	t_redirection		*redirection;
	struct s_commande	*next;
}	t_commande;


void	sig_handler(int sig);

void	tokenize_line(t_token **token, char *line, char **env);
t_token_word	*split_node_word(char *str, char **env);
t_token	*new_node_operator(char *word);
t_token_word	*new_node_word(char *str);
t_token	*new_node(t_token_word *word);
void	add_back(t_token **token, t_token *new);
void	add_back_word(t_token_word **token, t_token_word *new);
int		operator(char *word);
void	ft_free_token(t_token **stack);
void	free_split(char **tab);
void	fill_expandable(t_token_word *token);
char	*delete_quote(char *str);

int		ft_countwords(char const *s);
int		ft_len_word(char const *s);
char	*ft_mall(char const *s);
int		fr(char **result, int i);
char	**ft_split(char const *s);

// split_word
char	**ft_split_word(char const *s);
char	*ft_mall_word(char const *s);
int	ft_len_word_word(char const *s);
int	ft_countwords_word(const char *s);

int		quote_not_closed(char *str);
char    *clean_space(char *str);
int		is_double_operator(char *str);
int		ft_strlen(const char *str);
int		is_operator(char c);

char	**ft_cpy_envp(char **envp);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_env_value(char *var_name, char **env);
int		is_valid_var_char(char c);
void	expand(t_token_word *token, char **env);

void	print(t_token *stack);
void print_tokens(t_token *token);

int	check_syntax(t_token *tokens);
int	is_redirection(t_token_type type);
int	is_word(t_token *token);

int	count_words(t_token_word *word);
char	*join_token_words(t_token_word *word);
t_redirection *add_redirection(t_redirection **redir_list, t_token_type type, t_token_word *word);
char **append_arg(char **args, t_token_word *word);
t_commande	*convert_tokens_to_command(t_token *tokens);

void	free_args(char **args);
void	free_redirection(t_redirection *redir);
void	free_commande(t_commande *cmd);
void	print_redirection(t_redirection *redir);
void	print_commande(t_commande *cmd_list);

#endif