#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
void fatal(char *s1, char *s2 , int n)
{
    fprintf(stderr, "Error: %s,%s\n", s1, s2);
    exit(n);
}

void freelist(char **list)
{
    char **cp = list;
    for (; *cp; cp++)
        free(*cp);
    free(list);
    list = NULL;
}

void* emalloc(size_t n)
{
    void *rv;
    if((rv = malloc(n)) == NULL)
        fatal("malloc() failed", "", 1);
    return rv;
}

void* erealloc(void* p, size_t n)
{
    void* rv;
    if ((rv = realloc(p, n)) == NULL)
        fatal("realloc() failed", "", 1);
    return rv;
}
