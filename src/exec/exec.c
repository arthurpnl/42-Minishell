/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/09/29 19:13:56 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_dispatch(t_commande *cmd_list, t_shell_ctx *ctx)
{
	if (is_empty_cmd(cmd_list))
		return (ctx->last_status = 0);
	identify_cmd_type(cmd_list);
	if (!cmd_list->next)
	{
		if (cmd_list->type == CMD_BUILTIN)
			ctx->last_status = exec_builtin(cmd_list, ctx);
		else if (cmd_list->type == CMD_SIMPLE)
			ctx->last_status = exec_single_cmd(cmd_list, ctx);
		else if (cmd_list->type == CMD_ABSOLUTE
			|| cmd_list->type == CMD_RELATIVE)
			ctx->last_status = exec_absolute_cmd(cmd_list, ctx);
		else
			ctx->last_status = 1;
	}
	else
		ctx->last_status = exec_pipeline(cmd_list, ctx);
	return (ctx->last_status);
}

int	exec_single_cmd(t_commande *cmd_list, t_shell_ctx *ctx)
{
	char	*cmd_path;
	pid_t	pid;

	if (!cmd_list || !cmd_list->args)
		return (ctx->last_status = 1);
	if (!cmd_list->args[0] || cmd_list->args[0][0] == '\0')
		return (ctx->last_status = 0);
	pid = fork();
	if (pid == 0)
	{
		cmd_path = create_full_path(cmd_list, ctx->env);
		if (!cmd_path)
		{
			ft_putstr_fd(SHELL_NAME, 2);
			//ft_putstr_fd(cmd_list->args[0], 2);
			ft_putstr_fd(CMD_NOT_FOUND, 2);
			// ajouter l'input de l'user "xx: command not found"
			exit(127);
		}
		if (dispatch_redirect(cmd_list) != 0)
		{
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
		execve(cmd_path, cmd_list->args, ctx->env);
		perror(cmd_list->args[0]);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &ctx->last_status, 0);
		return (ctx->last_status >> 8);
	}
	else
		return (1);
}
int	exec_absolute_cmd(t_commande *cmd_list, t_shell_ctx *ctx)
{
	pid_t	pid;

	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);
	ctx->last_status = can_exec(cmd_list->args[0], ctx);
	if (ctx->last_status != 0)
		return (ctx->last_status);
	pid = fork();
	if (pid == 0)
	{
		if (dispatch_redirect(cmd_list) != 0)
			exit(EXIT_FAILURE);
		execve(cmd_list->args[0], cmd_list->args, ctx->env);
		perror(cmd_list->args[0]);
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &ctx->last_status, 0);
		return (ctx->last_status >> 8);
	}
	return (1);
}

int	exec_command_direct(t_commande *cmd_list, t_shell_ctx *ctx)
{
	char *cmd_path;

	if (cmd_list->type == CMD_SIMPLE)
	{
		cmd_path = create_full_path(cmd_list, ctx->env);
		if (!cmd_path)
			exit(127);
		execve(cmd_path, cmd_list->args, ctx->env);
		free(cmd_path);
	}
	else if (cmd_list->type == CMD_ABSOLUTE || cmd_list->type == CMD_RELATIVE)
		execve(cmd_list->args[0], cmd_list->args, ctx->env);
	exit(127);
}

int	exec_pipeline(t_commande *cmd_list, t_shell_ctx *ctx)
{
	pid_t pid;
	t_pipeline *pipeline;
	t_commande *curr;
	int i;
	int status = 0;

	i = 0;
	curr = cmd_list;
	pipeline = malloc(sizeof(t_pipeline));
	init_pipeline(pipeline, cmd_list, ctx->env);

	if (create_pipes(pipeline) != 0)
		return (1);

	while (curr)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			exec_child(curr, pipeline, ctx, i);
			exit(EXIT_FAILURE);
		}
		pipeline->pids[i] = pid;
		curr = curr->next;
		i++;
	}
	close_all_pipes(pipeline->pipes, pipeline->cmd_count);
	status = close_and_wait(pipeline, ctx);
	return (status);
}

void	exec_child(t_commande *cmd_list, t_pipeline *pipeline, t_shell_ctx *ctx,
		int i)
{
	if (pipeline->cmd_count > 1)
		handle_pipe_redirect(pipeline->pipes, i, pipeline->cmd_count);
	if (dispatch_redirect(cmd_list) != 0)
		exit(EXIT_FAILURE);
	if (cmd_list->type == CMD_BUILTIN)
		exit(exec_builtin(cmd_list, ctx));
	else
		exec_command_direct(cmd_list, ctx);
}

/*void exec_child(t_commande *cmd_list, t_pipeline *pipeline, char **env, int i)
{
	int	status;
	int	last_status;

	if (pipeline->cmd_count > 1)
		handle_pipe_redirect(pipeline->pipes, i, pipeline->cmd_count);
	if (dispatch_redirect(cmd_list) != 0)
		exit(EXIT_FAILURE);
	if (cmd_list->type == CMD_BUILTIN)
		exit(exec_builtin(cmd_list, env));
	else
		exec_command_direct(cmd_list, env);
}*/
int close_and_wait(t_pipeline *pipeline, t_shell_ctx *ctx)
{
	int i;
	int status;
	int last_status;

	if (!pipeline || !pipeline->pids)
		return (1);

	last_status = 0;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (waitpid(pipeline->pids[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	ctx->last_status = last_status;
	return (last_status);
}

int	exec_builtin_cmd(t_commande *cmd_list, t_shell_ctx *ctx)
{
	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);
	if (ft_strcmp(cmd_list->args[0], "echo") == 0)
		ctx->last_status = ft_echo(cmd_list->args);
	else if (ft_strcmp(cmd_list->args[0], "cd") == 0)
		ctx->last_status = ft_cd(cmd_list->args, ctx);
	else if (ft_strcmp(cmd_list->args[0], "pwd") == 0)
		ctx->last_status = ft_pwd();
	else if (ft_strcmp(cmd_list->args[0], "export") == 0)
		ctx->last_status = ft_export(cmd_list->args, ctx);
	else if (ft_strcmp(cmd_list->args[0], "unset") == 0)
		ctx->last_status = ft_unset(cmd_list->args, ctx);
	else if (ft_strcmp(cmd_list->args[0], "env") == 0)
		ctx->last_status = ft_env(ctx->env);
	else if (ft_strcmp(cmd_list->args[0], "exit") == 0)
		ctx->last_status = ft_exit(cmd_list->args, ctx);
	else
		ctx->last_status = 1;
	return (ctx->last_status);
}

int	exec_builtin(t_commande *cmd_list, t_shell_ctx *ctx)
{
	int	pid;

	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);
	if (!cmd_list->redirection)
		return (exec_builtin_cmd(cmd_list, ctx));
	pid = fork();
	if (pid == 0)
	{
		if (dispatch_redirect(cmd_list) != 0)
			exit(EXIT_FAILURE);
		exit(exec_builtin_cmd(cmd_list, ctx));
	}
	else if (pid > 0)
	{
		waitpid(pid, &ctx->last_status, 0);
		return (ctx->last_status >> 8);
	}
	return (ctx->last_status = 1);
}
