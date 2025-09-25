/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:50:11 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/02 14:18:30 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ctf;
	size_t			i;

	ptr = (unsigned char *)s;
	ctf = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (ptr[i] == ctf)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

/*
int main() {
	char arr[] = "Hello, World!";
	char *result = ft_memchr(arr, 'o', sizeof(arr));

	if (result != NULL) {
		printf("Trouvé: %c à l'adresse %p\n", *result, result);
	} else {
		printf("Caractère non trouvé\n");
	}

	return 0;
}
*/
