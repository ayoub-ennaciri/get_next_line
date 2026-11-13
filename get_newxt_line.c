#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>





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