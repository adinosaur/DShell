#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>
#include "smsh.h"

#define RIN '<'
#define ROUT '>'

int file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

int getRFileName(char *cmd, char *rfileName)
{
	int i;
	for(i = 0; cmd[i]; ++i)
	{
		if(cmd[i] == ROUT)
		{
			if (!cmd[i+1])
			{
				perror("缺少重定向文件名");
				exit(1);
			} else {
				cmd[i] = '\0';
				strcpy(rfileName, &cmd[i+1]);
				return i+1;
			}
		}
	}
	return -1;
}

int r_open(char* filename)
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

int r_close(int fd)
{
	dup2(fd, STDOUT_FILENO);
}

/*
int main()
{
	char rfileName[20];
	char cmd[] = "ls > test.txt";
	int res = getRFileName(cmd, rfileName);
	printf("rfileName : %s\n", rfileName);
	int fd = r_open(rfileName);
	printf("hello world\n");
	close(fd);
	printf("hello world\n");
	return 0;
}*/
