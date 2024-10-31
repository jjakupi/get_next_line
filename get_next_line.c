/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:09:44 by jjakupi           #+#    #+#             */
/*   Updated: 2024/10/31 18:19:00 by jjakupi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_leftovers_and_buffer(int fd, char *left_overs, char *buffer)
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

static char	*extract_line_from_leftovers(char *combined_da)
{
	ssize_t		i;
	char		*remaining_da;

	i = 0;
	if (!combined_da[i])
		return (NULL);
	while (combined_da[i] != '\n' && combined_da[i] != '\0')
		i++;
	if (combined_da[i] == 0 || combined_da[1] == 0)
		return (NULL);
	remaining_da = ft_substr(combined_da, i + 1, ft_strlen(combined_da) - i);
	if (*remaining_da == 0)
	{
		free(remaining_da);
		remaining_da = NULL;
	}
	combined_da[i + 1] = 0;
	return (remaining_da);
}

char	*get_next_line(int fd)
{
	static char			*remaining_da;
	char				*complete_line;
	char				*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remaining_da);
		free(buffer);
		remaining_da = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	complete_line = join_leftovers_and_buffer(fd, remaining_da, buffer);
	free(buffer);
	buffer = (NULL);
	if (!complete_line)
		return (NULL);
	remaining_da = extract_line_from_leftovers(complete_line);
	return (complete_line);
}
