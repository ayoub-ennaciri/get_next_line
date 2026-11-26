/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayennaci <ayennaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:19:35 by ayennaci          #+#    #+#             */
/*   Updated: 2026/11/26 12:35:52 by ayennaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ls_new(int fd)
{
	t_list	*node;
	char	*str;
	int		read_bytes;

	str = malloc(BUFFER_SIZE);
	if (!str)
		return (NULL);
	read_bytes = read(fd, str, BUFFER_SIZE);
	if (read_bytes <= 0)
		return (free(str), NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (free(str), NULL);
	node->read_bytes = read_bytes;
	node->buff = str;
	node->cursor = node->buff;
	node->pos = node->buff;
	node->nl_index = -1;
	node->next = NULL;
	return (node);
}

t_list	*get_last(t_list *head)
{
	while (head)
	{
		if (!head->next)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_list	*add_back(t_list *head, int fd)
{
	t_list	*last;

	last = get_last(head);
	last->next = ls_new(fd);
	if (!last->next)
		return (NULL);
	return (last->next);
}

int	find_nl(t_list *node)
{
	if (!node)
		return (1);
	while (node->cursor < node->buff + node->read_bytes)
	{
		if (*node->cursor == '\n')
			return (node->nl_index = node->cursor++ - node->buff);
		node->cursor++;
	}
	return (node->nl_index = -1);
}

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
