#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 10

typedef struct list
{
	char		*buff;
	char		*cursor;
	char		*pos;
	int			nl_index;
	int			read_bytes;
	struct list *next;	
} list;

char *get_next_line(int fd);

#endif