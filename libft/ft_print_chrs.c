/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:31:01 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/23 16:02:05 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_chr(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str == 0)
		return (ft_print_str("(null)"));
	while (str[i])
	{
		count += ft_print_chr(str[i]);
		i++;
	}
	return (count);
}
