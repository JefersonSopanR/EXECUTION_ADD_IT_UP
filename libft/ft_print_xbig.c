/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xbig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:12:53 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/21 15:11:28 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_bigx(long n, int base)
{
	char	*symbol;
	char	minus;
	int		count;

	minus = '-';
	symbol = "0123456789ABCDEF";
	if (n < 0)
	{
		ft_print_chr((int)minus);
		return (ft_print_bigx(-n, base) + 1);
	}
	else if (n < base)
		return (ft_print_chr(symbol[n]));
	else
	{
		count = ft_print_bigx(n / base, base);
		return (count + ft_print_bigx(n % base, base));
	}
}
