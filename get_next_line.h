#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#define	BUFF_SIZE	1024

typedef struct static_var
{
	char buff[BUFF_SIZE];
	long	size_read;
	int	nl_index;
	size_t	total;
}static_var;


char *get_next_line(int fd);

#endif