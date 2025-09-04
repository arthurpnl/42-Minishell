/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/09/04 16:55:28 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# define SHELL_NAME "minishell: "
# define CMD_NOT_FOUND " No such file or directory\n"

typedef enum	e_token_type
{
	TOK_WORD,			// 0
	TOK_PIPE,			// | = 1
	TOK_REDIR_IN,		// < = 2
	TOK_REDIR_OUT,		// > = 3
	TOK_REDIR_APPEND,	// >> = 4
	TOK_HEREDOC			// << = 5
}	t_token_type;

typedef enum	e_cmd_type
{
	CMD_SIMPLE,	// Commande simple -> Chercher dans PATH
	CMD_RELATIVE, // Chemin relatif (./cmd)
	CMD_ABSOLUTE, // Chemin absolu (/bin/cmd)
	CMD_BUILTIN,  // Commande builtin
	CMD_EMPTY // Cas erreur
} t_cmd_type;

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
	t_cmd_type			type;
	char				**path;
	struct s_commande	*next;
}	t_commande;

typedef struct s_pipeline
{
    t_commande *cmd_list;
    int    cmd_count;
    int    **pipes;
    pid_t  *pids;
    int    last_status;
    char   **env;
}    t_pipeline;

typedef struct s_shell_ctx
{
	int	last_status;
	char **env;
}	t_shell_ctx;

// main.c
void	sig_handler(int sig);
void	print(t_token *stack);
void print_tokens(t_token *token);
void	ft_free_token(t_token **stack);

// token.c
void	tokenize_line(t_token **token, char *line, char **env);
t_token	*new_node_operator(char *word);
int		operator(char *word);
void	add_back(t_token **token, t_token *new);
void	add_back_word(t_token_word **token, t_token_word *new);
void	free_split(char **tab);

// token_word.c
t_token_word	*split_node_word(char *str, char **env);
t_token	*new_node(t_token_word *word);
t_token_word	*new_node_word(char *str);
void	fill_expandable(t_token_word *token);
char	*delete_quote(char *str);

// ft_split_token.c
int		ft_countwords(char const *s);
int		ft_len_word(char const *s);
char	*ft_mall(char const *s);
int		fr(char **result, int i);
char	**ft_split(char const *s);

// ft_split_word.c
char	**ft_split_word(char const *s);
char	*ft_mall_word(char const *s);
int	ft_len_word_word(char const *s);
int	ft_countwords_word(const char *s);

// clean_space.c
char    *clean_space(char *str);
int		is_double_operator(char *str);
int		ft_strlen(const char *str);
int		is_operator(char c);

// quote_closed.c
int		quote_not_closed(char *str);

// expand.c
char	**ft_cpy_envp(char **envp);
char	*get_env_value(char *var_name, char **env);
void	expand(t_token_word *token, char **env);

// check_syntax.c
int	check_syntax(t_token *tokens);
int	is_redirection(t_token_type type);
int	is_word(t_token *token);

// token_to_command.c
int	count_words(t_token_word *word);
char	*join_token_words(t_token_word *word);
t_redirection *add_redirection(t_redirection **redir_list, t_token_type type, t_token_word *word);
char **append_arg(char **args, t_token_word *word);
t_commande	*convert_tokens_to_command(t_token *tokens);

// free_command.c
void	free_args(char **args);
void	free_redirection(t_redirection *redir);
void	free_commande(t_commande *cmd);
void	print_redirection(t_redirection *redir);
void	print_commande(t_commande *cmd_list);

// utils.c
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_valid_var_char(char c);
int		ft_strcmp(const char *s1, const char *s2);


// cmd_type.c
int	is_it_builtin(char *cmd_name);
void	identify_cmd_type(t_commande *cmd_list);

// exec.c
int	command_dispatch(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_single_cmd(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_absolute_cmd(t_commande *cmd_list, t_shell_ctx *ctx);
void exec_child(t_commande *cmd_list, t_pipeline *pipeline, t_shell_ctx *ctx, int i);
int	exec_pipeline(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_builtin(t_commande *cmd_list, t_shell_ctx *ctx);
int exec_command_direct(t_commande *cmd_list, t_shell_ctx *ctx);
int close_and_wait(t_pipeline *pipeline);

// exec_utils.c
char	**ft_split_ex(const char *s, char sep);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *s, int c, size_t n);
void	init_pipeline(t_pipeline *pipeline, t_commande *cmd_list, char **env);

// free.c
void	free_pipes(int **pipes, int count);
void	close_all_pipes(int **pipes, int count);

// here_doc.c
int	is_it_delimiter(char *line, char *delimiter);
int	handle_heredoc_redirect(t_redirection *redir);

// path.c
void	get_path_env(t_commande *cmd_list, char **env);
char	*create_full_path(t_commande	*cmd_list, char **env);

// pipeline.c
int    count_command (t_commande *cmd_list);
int    create_pipes(t_pipeline *pipeline);

// redirect.c
int    dispatch_redirect(t_commande *cmd_list);
int    handle_input_redirect(t_redirection *redir);
int    handle_output_redirect(t_redirection *redir);
int    handle_append_redirect(t_redirection *redir);
int    handle_pipe_redirect(int **pipes, int i, int cmd_count);

// builtins
int  ft_cd(char **args, char **env);
int  ft_echo(char **args);
int  ft_env(char **env);
int  ft_exit(char **args);
int  ft_export(char **args, char **env);
int  ft_pwd(void);
int  ft_unset(char **args, char **env);

#endif