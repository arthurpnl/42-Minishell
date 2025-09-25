/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:12:44 by mben-tha          #+#    #+#             */
/*   Updated: 2025/09/21 13:11:46 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countwords_word(const char *s)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
			count++;
		}
		while (s[i] && s[i] != '\'' && s[i] != '\"')
		{
			i++;
			count++;
		}
	}
	return (count);
}

static int	ft_len_word_word(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		quote = s[i++];
		while (s[i] && s[i] != quote)
			i++;
		if (s[i])
			i++;
	}
	else
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"')
			i++;
	}
	return (i);
}

static char	*ft_mall_word(char const *s)
{
	int		i;
	char	*dest;
	int		len;

	i = 0;
	len = ft_len_word_word(s);
	dest = malloc((ft_len_word_word(s) + 1) * sizeof(char));
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

char	**ft_split_word(char const *s)
{
	int			i;
	int			j;
	char		**result;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	result = malloc((ft_countwords_word(s) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[j])
	{
		result[i++] = ft_mall_word(&s[j]);
		if (fr(result, i - 1))
			return (NULL);
		j += ft_len_word_word(&s[j]);
	}
	result[i] = 0;
	return (result);
}