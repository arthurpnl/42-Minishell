/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:42:59 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/25 16:43:00 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

void	identify_cmd_type(t_commande *cmd_list)
{
	t_commande	*current;

	current = cmd_list;
	while (current)
	{
		if (current->args && current->args[0])
		{
			if (is_it_builtin(current->args[0]))
				current->type = CMD_BUILTIN;
			else if (current->args[0][0] == '/')
				current->type = CMD_ABSOLUTE;
			else if (current->args[0][0] == '.' && current->args[0][1] == '/')
				current->type = CMD_RELATIVE;
			else if (current->args[0][0] == '.' && current->args[0][1] == '.'
				&& current->args[0][2] == '/')
				current->type = CMD_RELATIVE;
			else
				current->type = CMD_SIMPLE;
		}
		else
			current->type = CMD_EMPTY;
		current = current->next;
	}
}
