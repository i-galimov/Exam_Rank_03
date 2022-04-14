#include <unistd.h>
#include <stdlib.h>
int ft_strlen(char *s) {
	int i = 0;
	while(s[i])
		i++;
	return(i);
}
char	*ft_strjoin(char *s1, char *s2) {
	int i = -1, j = -1;
	char *res;
	if (!s2)
		return(NULL);
	if (!s1) {
		res = malloc(2);
		res[0] = s2[0];
		res[1] = '\0';
		return(res);
	}
	res = malloc(sizeof(char) * ft_strlen(s1) + 2);
	if(!res)
		return(NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return(res);
}
char	*get_next_line(int fd) {
	char *res = NULL, *buf = malloc(2);
	if(!buf)
		return(NULL);
	while(read(fd, buf, 1) == 1 && buf[0] != '\0' && buf[0] != '\n') {
		buf[1] = '\0';
		res = ft_strjoin(res, buf);
	}
	free(buf);
	return(res);
}

/* // #include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

char	*get_next_line(int fd)
{
	int rd = 0;
	char	c;
	
	if ((rd = read(fd, &c, 1)) == 0)
		return (NULL); // Возвращаем NULL, если файл пустой
	
	char	*line = malloc(100000); // 1000000 для BigFile1
	char	*word = line;
	*line++ = c;
	while ((rd = read(fd, &c, 1)) > 0 && c != '\n')
		*line++ = c;
	if (c == '\n')
		*line++ = '\n';
	*line = '\0';
	return (word);
}
/*
int main() // main1.c
{
	char *line;
	line = get_next_line(0);
	while (line != NULL)
	{
		
		printf("%s", line);
		free (line);
		line = get_next_line(0);
	}
	return (0);

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <unistd.h>
#include <stdlib.h>

int get_next_line(char **line);

#endif
}*/