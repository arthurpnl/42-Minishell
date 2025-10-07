/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:57:30 by mehdi             #+#    #+#             */
/*   Updated: 2025/10/03 15:47:17 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	j = -1;
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[++j])
		dest[j] = s1[j];
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (free(s1), s1 = NULL, dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
