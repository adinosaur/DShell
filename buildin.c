#include <unistd.h>
#include <error.h>
#include <string.h>

int buildIn(char** av)
{
	if (strcmp(av[0], "cd") == 0)
	{
		cd(av[1]);
		return 1;
	}
	if (strcmp(av[0], "path") == 0)
	{
		return 1;
	}
	if (strcmp(av[0], "exit") == 0)
	{
		return 1;
	}
	else
		return 0;
}

void cd(char* path)
{
	if (path && chdir(path) < 0)
	{
		perror("没有那个文件或目录");
		exit(1);
	}
	return 0;
}
