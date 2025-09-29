/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_nofree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:54:44 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/26 15:55:22 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_nofree(char const *s1, char const *s2)
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