/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/09/04 17:01:00 by arthur           ###   ########.fr       */
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
#include <sys/stat.h>
#include <sys/types.h>
# include "../Libft/includes/libft.h"
# define SHELL_NAME "minishell: "
# define CMD_NOT_FOUND " command not found\n"

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
void	add_back_word(t_token_word **token, t_token_word *new);
t_token	*create_tok(char *word, t_shell_ctx *ctx, char **res, t_token **token);
int	tokenize_line(t_token **token, char *str, t_shell_ctx *ctx);
char	*delete_quote(char *str);
int	operator(char *word);
int	handle_token_error(char **res, t_token **token);

// token_word.c
t_token_word	*new_node_word(char *str);
t_token	*new_node(t_token_word *word);
t_token_word	*split_node_word(char *str, t_shell_ctx *ctx);

// ft_split_token.c
int		fr(char **result, int i);
char	**ft_split_token(char const *s);

// ft_split_word.c
char	**ft_split_word(char const *s);

// clean_space.c
char    *clean_space(char *str);
int		is_double_operator(char *str);
int		is_operator(char c);
int	skip_spaces(char *str, int i);
int	skip_spaces2(char *str, char *res, int i, int *j);
int	handle_quotes(char *str, char *res, int *i, int j);
int	handle_double_op(char *str, char *res, int *i, int j);

// quote_and_env.c
int	unclosed_quote(char *str);
char	**ft_cpy_envp(char **envp);
void	free_envp(char **envp);
void	free_token_words(t_token_word *head);
void	free_tokens(t_token *head);

// expand.c
char	*expand_dollar(char *res, const char *word, int *i, t_shell_ctx *ctx);
int		expand_token_word(t_token_word *token, t_shell_ctx *ctx);
int		is_valid_var_char(char c);
char	*expand_status(char *res, int status, int *i);

// check_syntax.c
int	check_syntax(t_token *tokens);
int	is_redirection(t_token_type type);
int	is_word(t_token *token);
int	print_pipe_error(void);
int	print_redir_error(t_token *next);
int	print_heredoc_error(void);

// token_to_command.c
int	count_words(t_token_word *word);
char	*join_token_words(t_token_word *word);
t_redirection *add_redirection(t_redirection **redir_list, t_token_type type, t_token_word *word);
char **append_arg(char **args, t_token_word *word);
t_commande	*tokens_to_command(t_token *tokens);

// free.c
void	free_args(char **args);
void	free_redirection(t_redirection *redir);
void	free_commande(t_commande *cmd);
void	free_split(char **split);

// print.c
void print_tokens(t_token *token);
void	print_redirection(t_redirection *redir);
void	print_commande(t_commande *cmd_list);

// utils.c
char	*ft_strjoin(char *s1, char const *s2);

// cmd_type.c
int	is_it_builtin(char *cmd_name);
void	identify_cmd_type(t_commande *cmd_list);

// exec.c
int	command_dispatch(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_single_cmd(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_absolute_cmd(t_commande *cmd_list, t_shell_ctx *ctx);
void exec_child(t_commande *cmd_list, t_pipeline *pipeline, t_shell_ctx *ctx, int i);
int	exec_pipeline(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_builtin_cmd(t_commande *cmd_list, t_shell_ctx *ctx);
int	exec_builtin(t_commande *cmd_list, t_shell_ctx *ctx); // tmp
int exec_command_direct(t_commande *cmd_list, t_shell_ctx *ctx);
int close_and_wait(t_pipeline *pipeline, t_shell_ctx *ctx);

// exec_utils.c
char	**ft_split_ex(const char *s, char sep);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *s, int c, size_t n);
void	init_pipeline(t_pipeline *pipeline, t_commande *cmd_list, char **env);
int	is_empty_cmd(t_commande *cmd);
int	can_exec(char *path, t_shell_ctx *ctx);

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
int	ft_cd(char **args, t_shell_ctx *ctx);
int	ft_echo(char **args);
int	ft_env(char **env);
int	ft_exit(char **args, t_shell_ctx *ctx);
int	ft_export(char **args, t_shell_ctx *ctx);
int	ft_pwd(void);
int	ft_unset(char **args, t_shell_ctx *ctx);

// export.c
int	add_o_update_env(t_shell_ctx *ctx, char *name, char *value);
int	update_var_env(t_shell_ctx *ctx, int i, char *name, char *value);
int	add_new_env(t_shell_ctx *ctx, char *name, char *value);
int	find_var_index(t_shell_ctx *ctx, char *name, char *value);
int	process_single_arg(char *arg, t_shell_ctx *ctx);
void	free_old_env(char **env);

// cd_utils.c
char	*get_path(void);
int	change_dir(char *target);
void	free_path(char *new_path, char *old_path);

// export_utils.c
char	**env_copy(char **env, char **new_env, int count);
int	export_without_args(t_shell_ctx *ctx);
int	parse_export_args(char *args, char **name, char **value);
int	is_valid_identifier(const char *name);
char	*build_new_entry(char *name, char *value);
void	print_declare_format(char *env_var);

// exit_utils.c
int	count_args(char **args);

#endif