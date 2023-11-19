/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:23:54 by dwilun            #+#    #+#             */
/*   Updated: 2023/11/19 11:45:54 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
char *get_next_line(int fd);

int main()
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);

    for (int i = 0; i < 5; i++)
    {
	   line = get_next_line(fd);
	   printf("%s", line);
    }
}
*/

/*
char	*ft_freecontent(char *fcontent)
{
	char	*new;
	int		start;
	int		size;

	if (!fcontent)
		return (NULL);
	start = 0;
	while (fcontent[start] != '\0' && fcontent[start] != '\n')
		start++;
	if (fcontent[start] == '\0')
		free(fcontent);
	if (fcontent[start] == '\0')
		return (NULL);
	size = start + 1;
	while (fcontent[size] != '\0')
		size++;
	new = ft_calloc(size - start + 1, sizeof(char));
	if (!new)
		return (NULL);
	size = 0;
	while (fcontent[start + 1] != '\0')
		new[size++] = fcontent[(start++) + 1];
	free(fcontent);
	return (new);
}
*/

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

/*
char	*ft_extractline(char *fcontent)
{
	int		i;
	char	*line;

	i = 0;
	if (!fcontent || fcontent[0] == '\0')
		return (NULL);
	while (fcontent[i] != '\0' && fcontent[i] != '\n')
		i++;
	line = ft_calloc(i + 1 + (fcontent[i] == '\n'), sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (fcontent[++i] != '\0' && fcontent[i] != '\n')
		line[i] = fcontent[i];
	if (fcontent[i] == '\n')
		line[i++] = '\n';
	fcontent[i] = '\0';
	return (line);
}
*/

char	*ft_readline(int fd, char *buffer, char *fcontent)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
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
	static char	*fcontent;
	char		*buffer;
	char		*line;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (ft_strchr(fcontent, '\n') == 0)
	{
		fcontent = ft_readline(fd, buffer, fcontent);
		if (!fcontent)
			return (NULL);
	}
	free(buffer);
	buffer = NULL;
	line = ft_extractline(fcontent);
	if (!line)
		return (NULL);
	fcontent = ft_freecontent(fcontent);
	return (line);
}
