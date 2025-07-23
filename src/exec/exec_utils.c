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

static int	count_words(const char *str, char sep)
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
	res = ft_calloc((count_words(s, sep) + 1), sizeof(*res));
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
