/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:52:32 by jesopan-          #+#    #+#             */
/*   Updated: 2024/04/18 18:35:04 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	num_words(const char *str, char c)
{
	int	count;
	int	target;

	count = 0;
	target = 0;
	while (*str)
	{
		if (*str != c && target == 0)
		{
			count++;
			target = 1;
		}
		else if (*str == c)
			target = 0;
		str++;
	}
	return (count);
}

static	char	*dup_word(const char *str, int start, int end)
{
	int		i;
	char	*word;
	int		length;

	i = 0;
	length = end - start;
	word = malloc(length + 1);
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		start;
	char	**split;

	j = 0;
	i = 0;
	start = 0;
	split = malloc(((num_words(s, c)) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i > start)
				split[j++] = dup_word(s, start, i);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		split[j++] = dup_word(s, start, i);
	split[j] = NULL;
	return (split);
}
