/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:38:08 by norabino          #+#    #+#             */
/*   Updated: 2025/01/09 15:08:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	char	*tmp;
	int		read_bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(remainder), NULL);
	read_bytes = 1;
	while (!ft_strchr(remainder, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(remainder), free(buffer), NULL);
		buffer[read_bytes] = 0;
		tmp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = tmp;
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

char	*ft_get_a_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[0] || !str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, 0, i + 1);
	if (!line)
	{
		free(str);
		return (NULL);
	}
	return (line);
}

char	*ft_new_remainder(char *remainder)
{
	int		i;
	char	*str;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	i++;
	str = ft_substr(remainder, i, ft_strlen(remainder) - i);
	if (!str)
	{
		free(remainder);
		return (NULL);
	}
	free(remainder);
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	if (!remainder)
		return (NULL);
	remainder = ft_read_to_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_a_line(remainder);
	remainder = ft_new_remainder(remainder);
	return (line);
}
