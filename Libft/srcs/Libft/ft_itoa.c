/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:34:42 by arpenel           #+#    #+#             */
/*   Updated: 2024/12/17 16:40:55 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	find_size(long nb)
{
	long	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		size++;
		nb = nb * (-1);
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	long	number;
	int		len;
	int		i;
	char	*str;

	number = nb;
	i = 0;
	len = find_size(number);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (number < 0)
	{
		str[0] = '-';
		number *= -1;
		i++;
	}
	while (len >= i)
	{
		str[len--] = (number % 10) + 48;
		number /= 10;
	}
	return (str);
}
