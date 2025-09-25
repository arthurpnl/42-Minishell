/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:28:17 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/17 16:39:40 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

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

char	**ft_split(const char *s, char sep)
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

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	char **tab = ft_split(argv[1], argv[2][0]);
// 	printf("TEST POURRIS = .%s \n", tab[1]);
// 	int	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }
