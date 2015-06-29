#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include "smsh.h"

/*
 * 为cmdlist申请的内存为BUFSIZ，有可能会溢出
 *
 */
int pipeTest(char *line, char **cmdlist)
{
	char *cp;
	int counter = 0;
	int bufspace = 0;
	cp = strtok(line, "|"); 
	while (cp != NULL)
	{
		//printf("cp=%s\n", cp);
		cmdlist[counter] = emalloc(strlen(cp) * sizeof(char) + 1);
		strcpy(cmdlist[counter], cp);
		cp = strtok(NULL, "|");
		counter++;
	}
	return counter;
}

/*
 * 注意父进程等待子进程结束，因此对于cmd1 | cmd2，
 * 应该是cmd2为父进程，cmd1作为子进程
 *
 */
void pipeCommand(char ** cmdlist)
{
	int num, i, status;
	int child_info = -1;
	pid_t pid, pid2;
	
	int filedes[2];
	pipe(filedes);
	
	pid = fork();
	if (pid > 0)
	{
		/*father*/
		//waitpid(pid, &status, 0);
		if (wait(&child_info) == -1)
			perror("wait");
	}
	else if (pid == 0)
	{
		/*child*/
		
		pid2 = fork();
		if (pid2 > 0)
		{
			dup2(filedes[1], 1);
			char** arglist = splitline(cmdlist[0]);
			
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execvp(arglist[0], arglist);
			
			waitpid(pid2, &status, 0);
		} else {
			dup2(filedes[0], 0);
			char** arglist = splitline(cmdlist[1]);
			
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);			
			execvp(arglist[0], arglist);
		}
	}
}

/*
int main()
{
	//char line[] = "cat hello.py | grep -n hello";
	char line[] = "ls -al | grep sh";
	char **cmdlist = emalloc(BUFSIZ);
	int num;
	
	num = pipeTest(line, cmdlist);
	
	if (num > 2)
		fatal("pipe", " only support one pipe now", 1);
		
	pipeCommand(cmdlist);
	freelist(cmdlist);
	return 0;
}*/

