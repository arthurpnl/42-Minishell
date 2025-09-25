/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:20:58 by arpenel           #+#    #+#             */
/*   Updated: 2025/02/15 12:53:58 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*cat_str;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	cat_str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!cat_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cat_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		cat_str[i++] = s2[j++];
	cat_str[i] = '\0';
	return (cat_str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	un_c;

	un_c = (unsigned char)c;
	while (*s)
	{
		if (*s == un_c)
			return ((char *)s);
		s++;
	}
	if (un_c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = malloc(sizeof(const char) * ft_strlen(s) + 1);
	i = 0;
	if (str)
	{
		str[ft_strlen(s)] = '\0';
	}
	else
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == 0)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= (unsigned int)ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (str != NULL)
			str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
