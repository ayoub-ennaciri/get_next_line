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
	new->start = buff;
	return (new);
}

list *add_back(list *head, list *new)
{
	while (head)
	{
		if (!head->new)
		{
			head->new = new;
			break;		
		}
		head = head->new;
	}
	
	return (new);
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

	i = node->current_index;
	while (i < node->read_bytes)
	{
		if ( (node->stash[i] == '\n' || !node->stash[i]))
		{
			node->current_index = i;
			return (node->nl_index = i);
		}
		i++;
	}
	node->current_index += i;
	node->nl_index = -1;
	return (-1);
}

char *give_me_line(list *start)
{
	int i;
	list *tmp;
	char *str;

	tmp = start;
	i = 0;
	while (tmp)
	{
		if (tmp->nl_index < 0)
			i += tmp->read_bytes;
		else 
			i += &tmp->stash[tmp->nl_index] - tmp->start;
		tmp = tmp->new; 
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	tmp = start;
	i = 0;
	int max = 0;
	char *copy = str;
	while (tmp)
	{
		if (tmp->nl_index < 0)
			max= tmp->read_bytes;
		else
			max = &tmp->stash[tmp->nl_index] - tmp->start;
		i = 0;
		if (max == 0)
			max = 1;
		while (i < max)
		{
			copy[i++] = *(tmp->start++);
		}
		copy = &copy[i];
		tmp = tmp->new;
	}
		copy[i] = 0;
	return (str);
}

char *get_next_line(int fd)
{
	static list *head;
	list *curnt;
	list *start;
	int lock;
	//char *str;

	if (!head)
	{
		head = ls_new(fd);
		if (!head)
			return (NULL);	
	}
	start = NULL;
	lock = 0;
	while (1)
	{
		curnt = get_last(head);
		if (curnt->read_bytes <= 0)
			return (clear(&head));
		if (curnt->current_index == curnt->read_bytes)
		{
			add_back(head, ls_new(fd));
			curnt = get_last(head);
		}
		curnt->nl_index = find_nl(curnt);
		if (!lock)
		{
			start = curnt;
			lock = 1;
		}
		if (curnt->nl_index < 0 )
		{
			continue;
		}
		//if (!start)
		//	start = curnt;
		lock = 0;
			return (give_me_line(start));  
		
	}
	
}

// read(fd, NULL, BUFFER_SIZE)
int main ()
{
	int fd = open("test.txt", O_RDONLY);
	char *ptr;
	for (size_t i = 0; i < 15; i++)
	{
		ptr = get_next_line(fd);
		printf("string : %s",ptr);
	}
	
	close(fd);
	return 0;
}