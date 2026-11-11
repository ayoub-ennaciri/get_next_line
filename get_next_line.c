#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>


list	*ls_new(int fd)
{
	list *new;
	char *buff;

	buff = malloc(BUFF_SIZE);
	if (!buff)
		return (NULL);
	new = malloc(sizeof(list));
	if (!new)
	{
		free(buff);
		return (NULL);
	}
	new->read_bytes = read(fd, buff, BUFF_SIZE);
	new->current_index = 0;
	new->nl_index = -1;
	new->stash = buff;
	return (new);
}

list *add_back(list **head, list *new)
{
	while (*head)
	{
		if (!(*head)->new)
		{
			(*head)->new = new;
			return (new);
		}
		else
			*head = (*head)->new;
	}
}

void delet_until(list **head, list *last)
{
	list *tmp;

	while (*head != last)
	{
		tmp = (*head)->new;
		free(*head);
		*head = tmp;
	}
}
char *clear(list **head)
{
	list *tmp;

	while (*head)
	{
		tmp = (*head)->new;
		free((*head)->stash);
		free(*head);
		*head = tmp;
	}
	return (NULL);
}

list *get_last(list *head)
{
	while (head)
	{
		if(!head->new)
			return (head);
		else
			head = head->new;
	}
	return (NULL);
}


int find_nl(list *node)
{
	int i;

	i = 0;
	while (node->current_index + i < node->read_bytes)
	{
		if (node->stash[i] == '\n' || !node->stash[i])
		{
			node->current_index += ++i;
			return (node->nl_index = i);
		}
		i++;
	}
	node->current_index += ++i;
	node->nl_index = -1;
	return (-1);
}


char *get_next_line(int fd)
{
	static list *head;
	list *curnt;
	char *str;

	if (!head)
	{
		head = ls_new(fd);
		if (!head)
			return (NULL);	
	}
	while (1)
	{
		curnt = get_last(head);
		if (curnt->read_bytes <= 0)
			return (clear(head));
		if (curnt->current_index == curnt->read_bytes)
		{
			
		}
	}
	
}

// read(fd, NULL, BUFFER_SIZE)
int main ()
{
	int fd = open("test.txt", O_RDONLY);
	char *ptr;
	for (size_t i = 0; i < 5; i++)
	{
		ptr = get_next_line(fd);
		printf("string : %s",ptr);
	}
	
	close(fd);
	return 0;
}