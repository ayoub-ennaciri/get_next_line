#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

list *ls_new(int fd)
{
	list	*node;

	node = malloc(sizeof(list));
	if (!node)
		return (NULL);
	node->buff = malloc(sizeof(BUFF_SIZE));
	if (!node->buff)
	{
		free(node);
		return (NULL);
	}
	node->read_bytes = read(fd, node->buff, BUFF_SIZE);
	//node->buff[BUFF_SIZE] = 0;
	node->cursor = node->buff;
	node->pos = node->buff;
	node->nl_index = -1;
	node->next = NULL;
	return (node);
}

void clean()
{
	
}

list	*get_last(list *head)
{
	while (head)
	{
		if (!head->next)
			return (head);
		head = head->next;
	}
	return (NULL);
}

list *add_back(list *head, int fd)
{
	list *last;

	last = get_last(head);
	last->next = ls_new(fd);
	if (!last->next)
		return (NULL);
	return (last->next);
}

int	find_nl(list *node)
{
	while (node->cursor < node->buff + node->read_bytes)
	{
		if (*node->cursor == '\n' || *node->cursor == 0)
			return (node->nl_index = node->cursor - node->buff);
		node->cursor++;
	}
	return (node->nl_index = -1);
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
		if (curnt->read_bytes > 0 && curnt->cursor == curnt->buff + curnt->read_bytes)
			add_back(head, fd);
		else if (curnt->read_bytes == 0 || find_nl(curnt) >= 0)
			return (give_me_line(start));
	}
	
}

// read(fd, NULL, BUFFER_SIZE)
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