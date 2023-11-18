#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif



char *get_next_line(int fd);

int main()
{
    int fd;
    char *line;

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

// utils functions
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	size_t	tot_l;
	char	*strj;

	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	tot_l = l1 + l2 + 1;
	strj = (char *)malloc(sizeof(char) * tot_l);
	if (!strj)
		return (NULL);
	strj[0] = '\0';
	ft_strlcat(strj, s1, l1 + 1);
	ft_strlcat(strj, s2, tot_l);
	strj[tot_l] = '\0';
	return (strj);
}

char	*ft_free_join(char *fcontent, char *buffer)
{
	int		i;
	char	*tmp;
	if (!fcontent)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
		if (!tmp)
			return (NULL);
		while (tmp[i] != '\0')
		{
			tmp[i] = buffer[i];
			i++;
		}
	}
}

char *ft_readline(int fd, char *buffer, char *fcontent)
{
	int bytes_read;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE + 1);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		fcontent = ft_strjoin(fcontent, buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*fcontent;
	char		*buffer;
	char		*line;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	fcontent = ft_readline(fd, buffer, fcontent);
}
