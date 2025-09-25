/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:36 by arpenel           #+#    #+#             */
/*   Updated: 2025/04/10 17:46:15 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_and_return_null(char *buffer, char *storage)
{
	free(buffer);
	free(storage);
	return (NULL);
}

// 1. Read the file and stock the data 
char	*readbuf(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	if (!storage)
		storage = ft_strdup("");
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_and_return_null(buffer, storage));
		buffer[bytes_read] = '\0';
		tmp = storage;
		storage = ft_strjoin(storage, buffer);
		free(tmp);
	}
	free(buffer);
	return (storage);
}

// 2. Extract the line 
char	*extract_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = ft_substr(storage, 0, i + 1);
	return (line);
}

// 3. Stock the rest of the line in a new variable
char	*clean_n_stock(char *storage)
{
	int		i;
	char	*tmp;
	char	*new_storage;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	tmp = storage;
	new_storage = ft_strdup(storage + i + 1);
	free(tmp);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = readbuf(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = clean_n_stock(storage);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/*
int	main(int ac, char **av)
{
	int		fd;
	char	*s;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while ((s = get_next_line(fd)) != NULL)
	{
		printf("%s", s);
		free(s);
	}
	close(fd);
	return (0);
}
*/