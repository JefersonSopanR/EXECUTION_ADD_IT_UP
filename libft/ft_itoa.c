/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:23:30 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/18 15:37:46 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static	int	digit_count(int n)
{
	int	digit;

	digit = !n;
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		is_negative;
	char	*str;
	int		i;

	is_negative = sign(n);
	i = digit_count(n) + is_negative;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (is_negative == 1)
	{
		*str = '-';
		str[--i] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (i-- - is_negative)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
