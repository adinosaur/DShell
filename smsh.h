#define YES 1
#define No  0

char *next_cmd();
char **splitline(char*);
void freelist(char**);
void *emalloc(size_t);
void *erealloc(void*, size_t);
int execute(char**);
void fatal(char*, char*, int);

/*buildin.c*/
int buildIn(char** av);
void cd(char*);

/*ioRedirection.c*/
int getRFileName(char *cmd, char *rfileName);
int r_open(char* filename);

/*pipe.c*/
int pipeTest(char *line, char **cmdlist);
void pipeCommand(char ** cmdlist);

