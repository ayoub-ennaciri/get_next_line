#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>


void clean()
{
	
}

char *give_me_line(list *start)
{
	list	*tmp;
	int 	len;
	char 	*str;
	char 	*copy;

	len = 0;
	tmp = start;
	while (tmp)
	{
		len += tmp->cursor - tmp->buff;
		tmp = tmp->next;
	}
	if (!len)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	tmp = start;
	copy = str;
	while (tmp)
	{
		while (tmp->pos < tmp->cursor)
			*copy++ = *tmp->pos++;
		tmp = tmp->next;
	}
	*copy = 0;
	return (str);
}

char *get_next_line(int fd)
{
	static list *head;
	list *curnt;
	list *start;

	if (!head)
		if (!(head = ls_new(fd)))
			return (NULL);
	start = NULL;
	while (1)
	{	
		curnt = get_last(head);
		if (!start)	
			start = curnt;
		if (find_nl(curnt) >= 0 || !curnt )
			return (give_me_line(start));
		else
			add_back(head, fd);
		
	}
	
}

int main ()
{
	int fd = open("test.txt", O_RDONLY);
	char *ptr;
	for (size_t i = 0; i < 20; i++)
	{
		ptr = get_next_line(fd);
		printf("string : |%s|\n",ptr);
	}
	//char str[20];
	//printf("%ld", read(fd,str, 20));
	close(fd);
	return 0;
}