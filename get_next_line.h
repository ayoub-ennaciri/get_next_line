#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

//#define BUFFER_SIZE 1024

typedef struct t_list
{
	char		*buff;
	char		*cursor;
	char		*pos;
	int			nl_index;
	int			read_bytes;
	struct t_list	*next;
}				t_list;

char			*get_next_line(int fd);
t_list			*ls_new(int fd);
t_list			*get_last(t_list *head);
t_list			*add_back(t_list *head, int fd);
int				find_nl(t_list *node);

#endif