/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/09/26 17:14:22 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dispatch_redirect(t_commande *cmd_list)
{
	t_redirection	*current;
	int				res;

	res = -1;
	current = cmd_list->redirection;
	while (current != NULL)
	{
		if (current->type == TOK_REDIR_IN)
			res = handle_input_redirect(current);
		else if (current->type == TOK_REDIR_OUT)
			res = handle_output_redirect(current);
		else if (current->type == TOK_REDIR_APPEND)
			res = handle_append_redirect(current);
		else if (current->type == TOK_HEREDOC)
		{
			res = handle_heredoc_redirect(current);
			if (res == 0)
			{
				dup2(current->fd, STDIN_FILENO);
				close(current->fd);
			}
		}
		if (res != 0)
			return (res);
		current = current->next;
	}
	return (0);
}

int	handle_input_redirect(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirect(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_append_redirect(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_pipe_redirect(int **pipes, int i, int cmd_count)
{
	int j;

	if (i == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (i > 0 && i < cmd_count - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else if (i == cmd_count - 1 && cmd_count > 1)
		dup2(pipes[i - 1][0], STDIN_FILENO);

	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	return (0);
}