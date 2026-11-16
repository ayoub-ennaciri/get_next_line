#include "get_next_line.h"

list *ls_new(int fd)
{
	list	*node;
	char *str;
	int read_bytes;
	
	str = malloc(BUFF_SIZE);
	if (!str)
	{
		//free(node);
		return (NULL);
	}
	read_bytes = read(fd, str, BUFF_SIZE);
	if (read_bytes <= 0)
	{
		free(str);
		return (NULL);
	}

	node = malloc(sizeof(list));
	if (!node)
		return (NULL);
	node->read_bytes = read_bytes;
	node->buff = str;
	//node->buff[BUFF_SIZE] = 0;
	node->cursor = node->buff;
	node->pos = node->buff;
	node->nl_index = -1;
	node->next = NULL;
	return (node);
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
			return (node->nl_index = node->cursor++ - node->buff);
		node->cursor++;
	}
	return (node->nl_index = -1);
}
