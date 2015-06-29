#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>
#include "smsh.h"

int file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

int getRFileName(char **av)
{
	int i;
	for(i = 0; av[i]; ++i)
	{
		if(strcmp(av[i], ROUT) == 0)
		{
			if (!av[i+1])
			{
				perror("缺少重定向文件名");
				exit(1);
			} else {
				return i+1;
			}
		}
	}
	return NULL;
}

int r_out(char* filename)
{
	int fd_out;

	if ((fd_out = open(filename, O_RDWR | O_CREAT, file_mode)) == -1)
	{
		perror("open error\n");
		exit(1);
	}
	
	if (dup2(fd_out, 1) == -1)
	{
		perror("dup2 error\n");
		exit(1);
	}
	
	return fd_out;
}
