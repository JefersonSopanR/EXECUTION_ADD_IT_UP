/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:47:26 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/17 20:28:36 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_digit(char a, int fd)
{
	write(fd, &a, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		print_digit('-', fd);
		n = -n;
	}
	if (n <= 9)
	{
		print_digit(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		print_digit(n % 10 + '0', fd);
	}
}
