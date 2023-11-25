#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char	*get_next_line(int fd);
char *extractline(char *str);

int main()
{
	int fd;
	char *line = "";

	fd = open("file.txt", O_RDONLY);
	//printf("dio cane\n");
	// while (line != NULL)
	// {
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	printf("ciaone\n");
	// }
	for (int i = 0; i < 10; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
}

char * dublicatestring(char *str)
{
	int i = 0;
	char *newstr;

	while (str[i] != '\0')
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\0')
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
char *strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *newstr;

	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	newstr = malloc(sizeof(char) * (i + j + 1));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}
char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*tmp;
	char	ch;

	ch = (char)c;
	tmp = (char *)s;
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i] != ch && tmp[i] != '\0')
		i++;
	
	if (tmp[i] == '\0' && tmp[i] != ch)
		return (NULL);
	return (tmp + i);
}

char *extractline(char *str)
{
	int i = 0;
	char *newstr;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	newstr = malloc(sizeof(char) * (i + 1 + (str[i] == '\n')));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		newstr[i] = str[i];
		i++;
	}
	if(str[i] == '\n')
	{
		newstr[i] = '\n';
		i++;
	}
	newstr[i] = '\0';
	return newstr;
}

int ft_strlen(char *str)
{
	//printf("ft_strlen\n");
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}


void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if ((nmemb * size) > 4294967295)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}
char *freebuff(char *str)
{
	//printf("freebuff\n");
	int start = 0;
	int size;
	char *newstr;

	if (!str)
		return (NULL);
	while (str[start] != '\n' && str[start] != '\0')
		start++;
	if (str[start] == '\0')
	{
		free(str);
		return (NULL);
	}
	size = start + 1;
	while (str[size] != '\0')
		size++;
	newstr = ft_calloc(size - start + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	size = 0;
	while (str[start + 1] != '\0')
		newstr[size++] = str[(start++) + 1];
	free (str);
	return (newstr);
}


char	*readline(int fd, char *buffer, char *str)
{
	char *tmp;
    int rr = 1;
	while (rr != 0)
	{
		rr = read(fd, buffer, BUFFER_SIZE);
		if (rr == -1)
			return (NULL);
		buffer[rr] = '\0';
		if (!str)
			str =  dublicatestring("");
		tmp = str;
		str = strjoin(tmp,buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return str;
}


char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*str;
	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		if (!str)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if(ft_strchr(str, '\n') == 0)
	{
		str = readline(fd, buffer, str);
		if (!str)
			return (NULL);
	}
	free(buffer);
	buffer = NULL;
	line = extractline(str);
	if (!line)
		return (NULL);
	str = freebuff(str);
	return (line);
}


// char *get_next_line(int fd)
// {
// 	char *buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	char *line;
// 	static char *str;
// 	str = readline(fd, buff, str);
// 	line = extractline(str);
// 	//printf("line = %s\n", line);
// 	//printf("tuamadre = %s\n", tuamadre);
// 	str = freebuff(str);
// 	//printf("tuamadre = '%s'\n", tuamadre);
// 	return (line);
// }