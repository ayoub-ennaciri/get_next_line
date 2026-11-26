/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayennaci <ayennaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:27:11 by ayennaci          #+#    #+#             */
/*   Updated: 2026/11/26 11:54:57 by ayennaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	clean(t_list **head)
{
	t_list	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->buff);
		free(*head);
		*head = tmp;
	}
}

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

static char *save (t_list *head, int fd)
{
	t_list			*curnt;
	t_list			*start;
	char			*result;

	start = NULL;
	while (1)
	{
		curnt = get_last(head);
		if (!start && curnt->cursor < curnt->buff + curnt->read_bytes)
			start = curnt;
		if (find_nl(curnt) >= 0)
		{
			result = give_me_line(start, &head);
			if (!(result))
				return (clean(&head), NULL);
			return (result);
		}
		else if (!add_back(head, fd))
		{
			if (start)
				return (give_me_line(start, &head));
			return (clean(&head), NULL);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head;

	if (!head)
	{
		head = ls_new(fd);
		if (!(head))
			return (NULL);
	}
	return (save(head, fd));
}
