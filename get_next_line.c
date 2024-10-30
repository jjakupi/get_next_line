/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:09:44 by jjakupi           #+#    #+#             */
/*   Updated: 2024/10/30 18:01:51 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*left_and_buffer(int fd, char *left_overs, char *buffer)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
		{
			free(buffer);
			return (NULL);
		}
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!left_overs)
			left_overs = ft_strdup("");
		temp = left_overs;
		left_overs = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_overs);
}

static char	*ex_line_from_left(char *line_b)
{
	ssize_t		i;
	char		*left_overs;

	i = 0;
	if (!line_b[i])
		return (NULL);
	while (line_b[i] != '\n' && line_b[i] != '\0')
		i++;
	if (line_b[i] == 0 || line_b[1] == 0)
		return (NULL);
	left_overs = ft_substr(line_b, i + 1, ft_strlen(line_b) - i - 1);
	if (*left_overs == 0)
	{
		free(left_overs);
		left_overs = NULL;
	}
	line_b[i + 1] = 0;
	return (left_overs);
}

char	*get_next_line(int fd)
{
	static char			*left_overs;
	char				*line;	
	char				*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_overs);
		free(buffer);
		left_overs = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = left_and_buffer(fd, left_overs, buffer);
	free(buffer);
	buffer = (NULL);
	if (!line)
		return (NULL);
	left_overs = ex_line_from_left(line);
	return (line);
}
