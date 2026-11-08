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

int ft_strlen(char *s)
{
	if (!s)
		return (0);
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_realloc(char *old, static_var *var)
{
	int size;
	char	*new;
	int i;
	size_t j;

	size = ft_strlen(old);
	if (var->size_read == BUFF_SIZE)
	size += BUFF_SIZE
	new = malloc(size + var->nl_index);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < size)
	{
		new[i] = old[i];
		i++;
	}
	free (old);
	while (i < var->size_read)
	{
		new[i] = var->buff[j];
		i++;
		j++;
	}
	return (new);
}

char *fill(static_var *var, char *old)
{
	char *new;
	int i;

	new = NULL;
	new = ft_realloc(old, var);
	if (!new)
		return (NULL);
	i = 0;
	while (i < var->nl_index)
	{
		new[i] = var->buff[i];
		i++;
	}
	new[i] = 0;
	return (new);
}



char *get_next_line(int fd)
{
	static static_var var;
	char *new;

	new = NULL;
	while (1)
	{
		var.size_read = read(fd, var.buff, BUFF_SIZE);
		if (var.size_read < 0)
			return (NULL);
		var.nl_index = find_nl(var.buff);
		if (var.nl_index < 0)
		{
			var.total += var.nl_index + 1;
			new = fill(&var, new);
			return (new);
		}
		else
		{
			var.total += BUFF_SIZE;
			new = ft_realloc(new, &var);
		}
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