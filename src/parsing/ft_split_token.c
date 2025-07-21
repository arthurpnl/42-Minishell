#include "minishell.h"

int	ft_countwords(const char *s)
{
	int		i;
	int		count;
	char 	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		count++;
		while (s[i] != ' ' && s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i++];
				while (s[i] && s[i] != quote)
					i++;
				if (s[i])
					i++;
			}
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
				i++;
		}
	}
	return (count);
}


int	ft_len_word(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i] != ' ' && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return (i);
}

char	*ft_mall(char const *s)
{
	int		i;
	char	*dest;
	int		len;

	i = 0;
	len = ft_len_word(s);
	dest = malloc((ft_len_word(s) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	fr(char **result, int i)
{
	if (result[i] == NULL)
	{
		while (i > 0)
		{
			i--;
			free(result[i]);
		}
		free(result);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s)
{
	int			i;
	int			j;
	char		**result;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	result = malloc((ft_countwords(s) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[j])
	{
		if (s[j] == ' ')
			j++;
		else
		{
			result[i++] = ft_mall(&s[j]);
			if (fr(result, i - 1))
				return (NULL);
			j += ft_len_word(&s[j]);
		}
	}
	result[i] = 0;
	return (result);
}