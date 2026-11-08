#include "get_next_line.h"
 #include <fcntl.h>
 #include <stdio.h>
int find_nl(char *s)
{
	ssize_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 0)
			return (i);
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (-1);
}

char *ft_realloc(char *old, size_t new_size)
{
	size_t size;
	char	*new;
	size_t i;

	size = sizeof(old);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = old[i]
		i++;
	}
	return (new);
}

char *fill(char *s, int len)
{
	char *new;
	int i;

	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

char *get_next_line(int fd)
{
	static static_var neces = {0};
	char *line;
	int	count;
	int nl;
	int i;


	i = 1;
	nl = -1;
	while (nl < 1)
	{
		neces.cur_indx = read(fd,  neces.buff, BUFF_SIZE);
		if (neces.cur_indx <= 0)
			return (NULL);
		neces.total += neces.cur_indx;
		nl = find_nl(neces.buff);
		if (nl >= 0)
		{
			line = malloc(neces.total + 1);
			if (!line)
				return (NULL);
			line = fill (neces.buff, nl);
		}
		else 
		{
			line = ft_realloc(line ,neces.total);
			if (!line)
				return (NULL);
		}
		i++;
	}
	return (NULL);
}


int main ()
{
	int fd = open("test.txt", O_RDWR);
	for (size_t i = 0; i < 5; i++)
	{
		/* code */
		printf("%s",get_next_line(fd));
	}
	
	close(fd);
	return 0;
}