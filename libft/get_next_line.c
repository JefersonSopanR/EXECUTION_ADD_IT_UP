/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:19:23 by jesopan-          #+#    #+#             */
/*   Updated: 2024/05/04 10:52:54 by jesopan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd, char *leftover, char *buffer)
{
	ssize_t		bytes_read;
	char		*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		temp = leftover;
		leftover = ft_strjoin(leftover, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftover);
}

static char	*leftover_from_line(char *line)
{
	char		*leftover;
	ssize_t		len;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == 0 || line[1] == 0)
		return (NULL);
	leftover = ft_substr(line, len + 1, ft_strlen(line) - len);
	if (*leftover == 0)
	{
		free(leftover);
		leftover = NULL;
	}
	len++;
	line[len] = '\0';
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char		*leftover;
	char			*line;
	char			*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(leftover);
		free(buffer);
		leftover = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_file(fd, leftover, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	leftover = leftover_from_line(line);
	return (line);
}
