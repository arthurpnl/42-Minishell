/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:53:09 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/23 11:12:19 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

static int	exit_shell(t_shell_ctx *ctx)
{
	printf("exit\n");
	free_envp(ctx->env);
	clear_history();
	exit(ctx->last_status);
}

static void	handle_unclosed_quote(char *input, t_shell_ctx *ctx)
{
	(void)ctx; // peut-être utile plus tard si tu veux set last_status
	printf("unclosed quote\n");
	free(input);
}

static void	process_input(char *input, t_shell_ctx *ctx)
{
	char	*str;
	t_token	*head;
	t_commande	*cmds;

	head = NULL;
	str = clean_space(input);
	free(input);
	if (!str)
	{
		perror("malloc_error");
		ctx->last_status = 1;
		return ;
	}
	if (tokenize_line(&head, str, ctx))
	{
		fprintf(stderr, "minishell: tokenize failed\n");
		free(str);
		ctx->last_status = 2;
		return ;
	}
	if (check_syntax(head))
	{
		free(str);
		free_tokens(head);
		ctx->last_status = 1;
		return ;
	}

	cmds = tokens_to_command(head);
	if (!cmds)
	{
		free(str);
		free_tokens(head);
		ctx->last_status = 1;
		return ;
	}

	// debug : afficher les tokens
	//printf("%s\n", str);
	//print_commande(cmds);
	//print_tokens(head);

	// ici tu lanceras l’exécution des tokens
	// et tu mettras à jour ctx->last_status en fonction du résultat
	ctx->last_status = command_dispatch(cmds, ctx);
	free(str);
	free_tokens(head);
	free_commande(cmds);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_shell_ctx	ctx;

	(void)ac;
	(void)av;
	if (!envp)
		return (0);
	ctx.env = ft_cpy_envp(envp);
	if (!ctx.env)
	{
		perror("malloc_error");
		return (1);
	}
	ctx.last_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (exit_shell(&ctx)); // libère ctx.env et sort proprement
		if (*input)
			add_history(input);
		if (unclosed_quote(input))
			handle_unclosed_quote(input, &ctx);
		else
			process_input(input, &ctx);
	}
	return (0);
}