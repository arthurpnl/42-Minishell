/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:31 by arthur            #+#    #+#             */
/*   Updated: 2025/09/29 18:33:12 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_words(const char *str, char sep)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static void	free_matrix(char **t)
{
	size_t	i;

	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
}

static char	*cpy_word(const char *str, char sep, size_t len)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_len_words(str, sep) + 1));
	if (!cpy)
		return (NULL);
	while (str[i] && i < len)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static int	count_words_ex(const char *str, char sep)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == sep) && str[i] != sep)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split_ex(const char *s, char sep)
{
	char	**res;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	res = ft_calloc((count_words_ex(s, sep) + 1), sizeof(*res));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == sep)
			i++;
		else
		{
			res[j] = cpy_word(&s[i], sep, ft_len_words(&s[i], sep));
			if (!res[j])
				return (free_matrix(res), NULL);
			j++;
			i += ft_len_words(&s[i], sep);
		}
	}
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, total);
	return (ptr);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n)
	{
		*str++ = (unsigned char)c;
		n--;
	}
	return (s);
}

void	init_pipeline(t_pipeline *pipeline, t_commande *cmd_list, char **env)
{
	pipeline->cmd_list = cmd_list;
	pipeline->cmd_count = count_command(cmd_list);
	pipeline->env = env;
	pipeline->last_status = 0;
	pipeline->pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	if (!pipeline->pids)
		exit(EXIT_FAILURE);
}

int	is_empty_cmd(t_commande *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->args[0][0] == '\0')
		return (1);
	return (0);
}

int	can_exec(char *path, t_shell_ctx *ctx)
{
	struct stat	infos;

	if (stat(path, &infos) != 0) // fichier non existant
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (ctx->last_status = 127);
	}
	if (!S_ISREG(infos.st_mode)) // type special ou repertoire
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("path", 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (ctx->last_status = 126);
	}
	if (!(infos.st_mode & S_IXUSR)) // pas de perm
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (ctx->last_status = 126);
	}
	return (0);
}

