#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char	*get_next_line(int fd);

int main(int argc, char **argv)
{
	int ciao = open("file.txt", O_RDONLY);
	char *result = get_next_line(0);
    printf("%s", result);
	//printf("char '%c' (%i)\n", result[530], result[530]);
}

char    *get_next_line(int fd)
{
    char buffer[1024];
	char tmp[1024];
    int test = read(fd, buffer, sizeof(buffer));
	int	i = 0;
	printf("Read return: %d\n", test);
	printf("fd: %d\n", fd);
	while(i < sizeof(buffer))
	{
		if(buffer[i] == '\n')
		{
			printf("New line\n");
			return tmp;
		}
		else if (buffer[i] == '\0')
		{
			printf("EOF\n");
			return tmp;
		}
		//printf("buffer[%i] '%c'\n", i, buffer[i], buffer[i]);
		//printf("%c", buffer[i]);
		tmp[i] = buffer[i];
		i++;
	}
    return (buffer);
}