#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

typedef struct list
{
	char		*stash;
	int			nl_index;
	int			current_index;
	int			read_bytes;
	struct list *new;	
} list;

char *get_next_line(int fd);

#endif