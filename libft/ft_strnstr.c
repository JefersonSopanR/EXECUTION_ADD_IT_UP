/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:06:38 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/16 19:48:42 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;

	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		j = 0;
		while (haystack[j] == needle[j] && needle[j] && j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack);
			j++;
		}
		haystack++;
		len--;
	}
	return (NULL);
}
