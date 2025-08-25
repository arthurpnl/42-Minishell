/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/08/25 14:39:48 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_dispatch(t_commande *cmd_list, char **env)
{
	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (0);

	identify_cmd_type(cmd_list);
	if(!cmd_list->next)
	{
		if (cmd_list->type == CMD_BUILTIN)
			return (exec_builtin(cmd_list, env));
		else if (cmd_list->type == CMD_SIMPLE)
			return (exec_single_cmd(cmd_list, env));
		else if (cmd_list->type == CMD_ABSOLUTE || cmd_list->type == CMD_RELATIVE)
			return (exec_absolute_cmd(cmd_list, env));
		else
			return (1); // error
	}
	else
		return (exec_pipeline(cmd_list, env));
}

int	exec_single_cmd(t_commande *cmd_list, char **env)
{
	char	*cmd_path;
	int	status;
	pid_t	pid;

	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);
	pid = fork();
	if  (pid == 0)
	{
		cmd_path = create_full_path(cmd_list, env);
		if (!cmd_path)
		{
			ft_putstr_fd(SHELL_NAME, 2);
			ft_putstr_fd(cmd_list->args[0], 2);
			ft_putstr_fd(CMD_NOT_FOUND"\n", 2); // ajouter l'input de l'user "xx: command not found"
			exit (127);
		}
        if (dispatch_redirect(cmd_list) != 0)
            exit(EXIT_FAILURE);
		execve(cmd_path, cmd_list->args, env);
		perror(cmd_list->args[0]);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (status >> 8);
	}
	else
		return (1);
}

int	exec_absolute_cmd(t_commande *cmd_list, char **env)
{
	int	status;
	pid_t	pid;

	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);
	if (access(cmd_list->args[0], X_OK) != 0)
	{
		perror(cmd_list->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
        if (dispatch_redirect(cmd_list) != 0)
            exit(EXIT_FAILURE);
		execve(cmd_list->args[0], cmd_list->args, env);
		perror(cmd_list->args[0]);
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (status >> 8);
	}
	else
		return (1);
}

void exec_child(t_commande *cmd_list, t_pipeline *pipeline, char **env, int i)
{
    if (pipeline->cmd_count > 1)
        handle_pipe_redirect(cmd_list->redirection, cmd_list, pipeline->pipes, i);
    if (dispatch_redirect(cmd_list) != 0)
        exit(EXIT_FAILURE);
    if (cmd_list->type == CMD_BUILTIN)
        exit(exec_builtin(cmd_list, env));
    else if (cmd_list->type == CMD_ABSOLUTE)
        exec_absolute_cmd(cmd_list, env);
    else if (cmd_list->type == CMD_RELATIVE)
        exec_absolute_cmd(cmd_list, env);
}

int	exec_pipeline(t_commande *cmd_list, char **env)
{
    pid_t    pid;
    t_pipeline    *pipeline;
    t_commande    *curr;
	int	i;

	i = 0;
    curr = cmd_list;
	pipeline = malloc(sizeof(t_pipeline));
	init_pipeline(pipeline);
    pipeline->cmd_list = cmd_list;
    pipeline->cmd_count = count_command(cmd_list);
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
            exec_child(curr, pipeline, env, i);
			exit(EXIT_FAILURE);
		}
        curr = curr->next;
		i++;
    }
    close_and_wait(pipeline);
    return (0);
}

void close_and_wait(t_pipeline *pipeline)
{
	close_all_pipes(pipeline->pipes, pipeline->cmd_count);
	while (wait(NULL) > 0)
            ;
	free_pipes(pipeline->pipes, pipeline->cmd_count);
}

int	exec_builtin(t_commande *cmd_list, char **env)
{
	if (!cmd_list || !cmd_list->args || !cmd_list->args[0])
		return (1);

	if (ft_strcmp(cmd_list->args[0], "echo") == 0)
		return (ft_echo(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "cd") == 0)
		return (ft_cd(cmd_list->args, env));
	else if (ft_strcmp(cmd_list->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd_list->args[0], "export") == 0)
		return (ft_export(cmd_list->args, env));
	else if (ft_strcmp(cmd_list->args[0], "unset") == 0)
		return (ft_unset(cmd_list->args, env));
	else if (ft_strcmp(cmd_list->args[0], "env") == 0)
		return (ft_env(env));
	else if (ft_strcmp(cmd_list->args[0], "exit") == 0)
		return (ft_exit(cmd_list->args));
	return (1);
}



