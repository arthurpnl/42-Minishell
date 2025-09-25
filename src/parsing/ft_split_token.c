/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:12:44 by mben-tha          #+#    #+#             */
/*   Updated: 2025/09/19 16:44:28 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len_word(const char *s, int i)
{
	char	quote;

	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static int	ft_countwords(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		count++;
		i = ft_len_word(s, i);
	}
	return (count);
}

static char	*ft_mall(char const *s)
{
	int		i;
	char	*dest;
	int		len;

	i = 0;
	len = ft_len_word(s, 0);
	dest = malloc((len + 1) * sizeof(char));
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

char	**ft_split_token(char const *s)
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
			j += ft_len_word(&s[j], 0);
		}
	}
	result[i] = 0;
	return (result);
}