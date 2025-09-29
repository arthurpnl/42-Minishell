/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:47:50 by arthur            #+#    #+#             */
/*   Updated: 2025/09/26 17:14:08 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_delimiter(char *line, char *delimiter)
{
	size_t	delimiter_len;

	if (!line)
		return (1);
	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0)
	{
		if (line[delimiter_len] == '\n' || line[delimiter_len] == '\0')
			return (1);
	}
	return (0);
}

int	handle_heredoc_redirect(t_redirection *redir)
{
	int pipe_fd[2];
	char *line;

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Pipe creation failed for here_doc", 2);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("heredoc>");
		if (is_it_delimiter(line, redir->file) == 1)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	redir->fd = pipe_fd[0];
	return (0);
}
