/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/07/29 15:13:10 by arthur           ###   ########.fr       */
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
			return (exec_single_cmd(cmd_list, env);
		else if (cmd_list->type == CMD_ABSOLUTE)
			return(exec_absolute_cmd(cmd_list, env));
		else if (cmd_list->type == CMD_RELATIVE)
			return(exec_relative_cmd(cmd_list, env));
		else
			return (1) // error
	}
	else
	return (exec_pipeline(cmd_list, env));
}

int	exec_single_cmd(t_commande *cmd_list, char **env, int i)
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

int	exec_pipeline(t_commande *cmd_list, char **env)
{
 // a faire
}

int	execute(t_commande *cmd_list, char	**env)
{
	if (!cmd_list->args)
		return (0);
	if (cmd_list->args->next == NULL)
		return(exec_cmd(cmd_list, env), 0);
	else if(cmd_list->args->next != NULL)
		return (exec_cmd(cmd_list, env), 0);
	return (0);
}