/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:56:34 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/12 12:30:12 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
