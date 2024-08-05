/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:20:07 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/16 19:48:03 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	count;

	j = 0;
	i = 0;
	count = 0;
	while (src[count] != '\0')
	{
		count++;
	}
	while (dst[j] != '\0' && j < dstsize)
	{
		j++;
	}
	while (src[i] != '\0' && (i + j + 1) < dstsize)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j != dstsize)
	{
		dst[j + i] = '\0';
	}
	return (j + count);
}
