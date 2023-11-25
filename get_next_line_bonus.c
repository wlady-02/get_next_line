/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:23:54 by dwilun            #+#    #+#             */
/*   Updated: 2023/11/25 11:51:58 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_freecontent(char *fcontent)
{
	char	*tmp;
	int		start;
	int		size;

	start = 0;
	if (fcontent == NULL)
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	if (fcontent[start] == '\0')
	{
		free (fcontent);
		return (NULL);
	}
	size = start + 1;
	while (fcontent[size] != '\0')
		size++;
	tmp = ft_calloc(size - start + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (fcontent[start + 1] != '\0')
		tmp[size++] = fcontent[(start++) + 1];
	free(fcontent);
	return (tmp);
}

char	*ft_extractline(char *fcontent)
{
	char	*line;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (fcontent == NULL || fcontent[0] == '\0')
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	line = ft_calloc(start + 1 + (fcontent[start] == '\n'), sizeof(char));
	if (line == NULL)
		return (NULL);
	if (fcontent[start] == '\n')
		start++;
	while (i < start && fcontent[i] != '\0')
	{
		line[i] = fcontent[i];
		i++;
	}
	return (line);
}

char	*ft_readline(int fd, char *buffer, char *fcontent)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!fcontent)
			fcontent = ft_calloc(2, sizeof(char));
		tmp = fcontent;
		fcontent = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (fcontent);
}

char	*get_next_line(int fd)
{
	static char	*fcontent[4096];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strchr(fcontent[fd], '\n') == NULL)
		fcontent[fd] = ft_readline(fd, buffer, fcontent[fd]);
	free(buffer);
	line = ft_extractline(fcontent[fd]);
	if (!line)
	{
		free(fcontent[fd]);
		fcontent[fd] = NULL;
		return (NULL);
	}
	fcontent[fd] = ft_freecontent(fcontent[fd]);
	return (line);
}