/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:34:51 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/05 17:03:12 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (dst_size > 0)
	{
		while (src[i] && i < (dst_size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}

/*
int	main()
{
	char	dest[10];
	const	char *src = "Hello World !";
	size_t	len = ft_strlcpy(dest, src, sizeof(dest));

	printf("Copied string : %s\n", dest);
	printf("Lenght of source : %zu\n", len);

	return (0);
}
*/