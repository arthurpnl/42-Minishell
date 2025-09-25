/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:31:43 by arpenel           #+#    #+#             */
/*   Updated: 2025/04/10 17:47:12 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_pointer(void *ptr, size_t *count)
{
	unsigned long	adr;

	if (!ptr)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	adr = (unsigned long)ptr;
	ft_putstr("0x", count);
	ft_putnbr_base(adr, "0123456789abcdef", count);
}

static void	ft_check_type(char c, va_list ap, size_t *count)
{
	if (c == 'c')
		ft_putchar(va_arg(ap, int), count);
	else if (c == 'p')
		ft_put_pointer(va_arg(ap, void *), count);
	else if (c == 's')
		ft_putstr(va_arg(ap, char *), count);
	else if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(ap, int), count);
	else if (c == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", count);
	else if (c == 'x')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", count);
	else if (c == '%')
		ft_putchar('%', count);
	else
		return ;
}

static char	*ft_print_n_find(const char *str, va_list ap, size_t *count)
{
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_check_type(*str, ap, count);
		}
		else
			ft_putchar(*str, count);
		str++;
	}
	return ((char *)str);
}

int	ft_printf(const char *format, ...)
{
	size_t	count;
	va_list	ap;

	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	ft_print_n_find(format, ap, &count);
	va_end(ap);
	return (count);
}
