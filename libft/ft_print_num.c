/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:02:52 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/21 14:54:35 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_num(long n, int base)
{
	int		count;
	char	*symbol;
	char	minus;

	minus = '-';
	symbol = "0123456789abcdef";
	if (n < 0)
	{
		ft_print_chr((int)minus);
		return (ft_print_num(-n, base) + 1);
	}
	else if (n < base)
	{
		return (ft_print_chr(symbol[n]));
	}
	else
	{
		count = ft_print_num(n / base, base);
		return (count + ft_print_num(n % base, base));
	}
}
