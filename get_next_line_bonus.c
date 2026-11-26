#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>


void	clean_until(t_list **head, t_list *until)
{
	t_list	*tmp;

	tmp = NULL;
	while (*head && *head != until)
	{
		free((*head)->buff);
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

char	*give_me_line(t_list *start, t_list **head)
{
	t_list	*tmp;
	int		len;
	char	*str;
	char	*copy;

	len = 0;
	tmp = start;
	while (tmp && tmp->pos < tmp->cursor)
	{
		len += tmp->cursor - tmp->pos;
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
	*copy = '\0';
	tmp = start;
	while (tmp && tmp->pos == tmp->cursor)
		tmp = tmp->next;
	if (tmp)
		clean_until(head, tmp);
	return (str);
}

char	*function(int fd, t_list **head)
{
	t_list	*curnt;
	t_list	*start;
	char	*result;

	if (!(*head))
		if (!((*head) = ls_new(fd)))
			return (NULL);
	start = NULL;
	while (1)
	{
		curnt = get_last((*head));
		if (!start && curnt->cursor < curnt->buff + curnt->read_bytes)
			start = curnt;
		if (find_nl(curnt) >= 0)
		{
			if (!(result = give_me_line(start, &(*head))))
			{
				clean(&(*head));
				return (NULL);
			}
			return (result);
		}
		else if (!add_back((*head), fd))
		{
			if (start)
				return (give_me_line(start, &(*head)));
			clean(&(*head));
			return (NULL);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list *arry[1024];
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (function(fd, &arry[fd]));
}