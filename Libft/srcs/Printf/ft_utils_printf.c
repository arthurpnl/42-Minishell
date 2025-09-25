/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:29:21 by arpenel           #+#    #+#             */
/*   Updated: 2025/04/10 18:29:21 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, size_t *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putnbr(int n, size_t *count)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, count);
	ft_putchar((nb % 10) + '0', count);
}

void	ft_putnbr_base(unsigned long nbr, char *base, size_t *count)
{
	unsigned long	nb;
	unsigned long	len_base;

	nb = nbr;
	len_base = ft_strlen_count(base);
	if (nb == 0)
	{
		ft_putchar(base[0], count);
		return ;
	}
	if (nb > 0 && nb < len_base)
		ft_putchar(base[nb], count);
	if (nb >= len_base)
	{
		ft_putnbr_base(nb / len_base, base, count);
		ft_putnbr_base(nb % len_base, base, count);
	}
}

void	ft_putstr(char *str, size_t *count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

int	ft_strlen_count(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
