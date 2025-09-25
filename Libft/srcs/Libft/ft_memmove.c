/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:33:25 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/02 14:18:43 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src || n == 0)
		return (dest);
	if ((unsigned char *)dest < (unsigned const char *)src)
	{
		while (n--)
		{
			((unsigned char *)dest)[i] = ((unsigned const char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n--)
		{
			((unsigned char *)dest)[n] = ((unsigned const char *)src)[n];
		}
	}
	return (dest);
}
