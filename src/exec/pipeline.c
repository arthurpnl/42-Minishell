/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:45:25 by arthur            #+#    #+#             */
/*   Updated: 2025/08/25 14:55:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_command(t_commande *cmd_list)
{
	int			i;
	t_commande	*current;

	current = cmd_list;
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	create_pipes(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (pipeline->cmd_count <= 1)
	{
		pipeline->pipes = NULL;
		return (0);
	}
	pipeline->pipes = malloc(sizeof(int *) * (pipeline->cmd_count - 1));
	if (!pipeline->pipes)
		return (-1);
	while (i < pipeline->cmd_count - 1)
	{
		pipeline->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipeline->pipes[i])
			return (free_pipes(pipeline->pipes, i), -1);
		if (pipe(pipeline->pipes[i]) == -1)
			return (free_pipes(pipeline->pipes, i + 1), -1);
		i++;
	}
	return (0);
}
