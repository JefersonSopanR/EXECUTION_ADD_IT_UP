/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:38:02 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/23 15:33:07 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char specifier, va_list arg)
{
	size_t	count;

	count = 0;
	if (!specifier)
		return (0);
	if (specifier == 'c')
		count += ft_print_chr(va_arg(arg, int));
	if (specifier == 's')
		count += ft_print_str(va_arg(arg, char *));
	if (specifier == 'p')
		count += ft_print_void(va_arg(arg, unsigned long long));
	if (specifier == 'd')
		count += ft_print_num(((long)va_arg(arg, int)), 10);
	if (specifier == 'i')
		count += ft_print_num((long)va_arg(arg, int), 10);
	if (specifier == 'u')
		count += ft_print_num(va_arg(arg, unsigned int), 10);
	if (specifier == 'x')
		count += ft_print_num(((long)va_arg(arg, unsigned int)), 16);
	if (specifier == 'X')
		count += ft_print_bigx(((long)va_arg(arg, unsigned int)), 16);
	if (specifier == '%')
		count += ft_print_chr(specifier);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), args);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
