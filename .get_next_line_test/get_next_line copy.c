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
	char *line;

	fd = open("file.txt", O_RDONLY);
	//printf("dio cane\n");
	for (int i = 0; i < 2; i++)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
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
int strchr(char *str, char c)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *extractline(char *str)
{
	//printf("extractline\n");
	//printf("str = %s\n", str);
	int i = 0;
	char *newstr;
	while (str[i] != '\0' && str[i] != '\n')
	{
		newstr[i] = str[i];
		printf("%c", newstr[i]);
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
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = -1;
	if (start > ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	s += start;
	if (ft_strlen(s) <= len)
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		substr[i] = s[i];
	substr[i] = '\0';
	return (substr);
}
char *freebuff(char *str)
{
	//printf("freebuff\n");
	int i = 0;
	int j = 0;
	char *newstr;

	if (str[0] == '\0' || !str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
	{
		free(str);
		return (NULL);
	}
	newstr = str;
	str = ft_substr(newstr, i + 1, ft_strlen(str) - i);
	free (newstr);
	return (str);
}

// char *freebuff(char *buff)
// {
// 	//printf("freebuff\n");
// 	//printf("buff = %s\n", buff);
// 	int fake_len = fake_strlen(buff);
// 	int len = ft_strlen(buff);
// 	char *tmp;
// 	len -= fake_len;
// 	tmp = buff;
// 	buff = ft_substr(buff, fake_len + 1, len);
// 	free(buff);
// 	return (buff);
// }

char    *readline(int fd, char *buffer, char *tuamadre)
{
	
	char *salario;
    int test = 1;

	while (test != 0)
	{
		//printf("test = %i\n", test);
		test = read(fd, buffer, BUFFER_SIZE);
		buffer[test] = '\0';
		if (!tuamadre)
			tuamadre =  dublicatestring("");
		salario = tuamadre;
		tuamadre = strjoin(salario,buffer);
		free(salario);
		if (strchr(buffer, '\n'))
			break ;
	}
	// printf(	"\nCattivone\n");
	// printf("tuamadre = %s\n", tuamadre);
	// printf("\ndio cane: %s\n" ,extractline(tuamadre));
	return tuamadre;


	// while(i < BUFFER_SIZE)
	// {
	// 	if(buffer[i] == '\n')
	// 	{
	// 		printf("New line\n");
	// 		return buffer;
	// 	}
	// 	else if (buffer[i] == '\0')
	// 	{
	// 		printf("buffer[%i] '%c', (%i)\n", i, buffer[i], buffer[i]);
	// 		printf("EOF\n");
	// 		return buffer;
	// 	}
	// 	//printf("buffer[%i] '%c'\n", i, buffer[i], buffer[i]);
	// 	//printf("%c", buffer[i]);
	// 	//printf("i = %i\n", i);

	// 	i++;
	// }
	// buffer[i] = '\0';
}


char *get_next_line(int fd)
{
	char *buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	char *line;
	static char *tuamadre;
	tuamadre = readline(fd, buff, tuamadre);
	line = extractline(tuamadre);
	//printf("line = %s\n", line);
	//printf("tuamadre = %s\n", tuamadre);
	//tuamadre = freebuff(tuamadre);
	//printf("tuamadre = '%s'\n", tuamadre);
	return (line);
}