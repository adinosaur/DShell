#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "smsh.h"

#define DFL_PROMPT "> "

int main()
{
	char *cmdline, *prompt, **arglist, **cmdlist;
	int result, fd_out, i, fno, cmdNum;
	void setup();

	prompt = DFL_PROMPT;
	setup();

	cmdlist = emalloc(BUFSIZ);
	while ((cmdline = next_cmd(prompt, stdin)) != NULL)
	{
		/* pipe test*/
		cmdNum = pipeTest(cmdline, cmdlist);
		if (cmdNum == 1)
		{
			if ((arglist = splitline(cmdline)) != NULL)
			{
				if (buildIn(arglist))
				{
					;
				} else {
					result = execute(arglist);
					freelist(arglist);
				}
			}
		} 
		else if (cmdNum == 2) 
		{
			pipeCommand(cmdlist);
		}
		//freelist(cmdlist);
		free(cmdline);
	}
	return 0;
}

void setup()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}


