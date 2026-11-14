#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void *clear(list *head)
{
	list *tmp;

	while (head)
	{
		tmp = (head)->next;
		free((head)->stash);
		free(head);
		head = tmp;
	}
	return (NULL);
}

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
	if (new->read_bytes <= 0)
		return (NULL);
	new->nl_index = -1;
	new->stash = buff;
	new->start = buff;
	return (new);
}

list *add_back(list **head,list *new)
{
	list *tmp;

	tmp = *head;
	while (tmp)
	{
		if (!(tmp)->next)
		{
			(tmp)->next = new;
			break;
		}
		(tmp) = (tmp)->next;
	}
	if (!*head && new)
		return (*head = new);
	else if (!new)
		return (clear(*head));
	return (new);
}

void delet_until(list **head, list *last)
{
	list *tmp;

	while (*head != last)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}


list *get_last(list *head)
{
	while (head)
	{
		if(!head->next)
			return (head);
		else
			head = head->next;
	}	
	return (NULL);
}


int find_nl(list *node)
{
	int i;

	i = 0;
	while (node->start + i < node->stash + node->read_bytes)
	{
		if ( (*(node->start + i) == '\n' || !*(node->start + i)))
			return (node->nl_index = i);
		i++;
	}
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
		tmp = tmp->next; 
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
		if (max == 0 && !tmp->nl_index)
		{
			max = 1;
			tmp->read_bytes -= 1;
		}
		while (i < max)
		{
			copy[i++] = *(tmp->start++);
		}
		copy = &copy[i];
		tmp = tmp->next;
	}
		copy[i] = 0;
	return (str);
}

char *get_next_line(int fd)
{
	static list *head;
	list *curnt;
	list *start;

	start = NULL;
	while (1)
	{
		curnt = get_last(head);
		if (!head || find_nl(curnt) == -1)
		{
			if (!start)
			start = curnt;
			if (!add_back(&head, ls_new(fd))) 
				return (NULL);
			curnt = get_last(head);
		}
		if (curnt->read_bytes <= 0)
			return (clear(head));
		
		if (curnt->nl_index < 0)
			continue;
		//start = NULL;
			return (give_me_line(start));
	}
}

char *get_next_line(int fd)
{
	list *head;

	while (1)
	{
		/* code */
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