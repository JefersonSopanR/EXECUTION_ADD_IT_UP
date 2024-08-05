/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_void.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:54:08 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/23 16:17:33 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_counter(unsigned long long ptr)
{
	int	count;

	count = 0;
	while (ptr > 0)
	{
		count++;
		ptr /= 16;
	}
	return (count);
}

static void	print_number(unsigned long long ptr)
{
	char	*symbol;

	symbol = "0123456789abcdef";
	if (ptr >= 16)
	{
		print_number(ptr / 16);
		print_number(ptr % 16);
	}
	else
	{
		ft_print_chr(symbol[ptr]);
	}
}

int	ft_print_void(unsigned long long ptr)
{
	int		count;

	count = 0;
	count += ft_print_str("0x");
	if (ptr == 0)
	{
		count += ft_print_chr('0');
	}
	else
	{
		print_number(ptr);
		count += ft_print_counter(ptr);
	}
	return (count);
}
