#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    fd_putstr(char *str, int fd);
char    *_substr(char *str, int s, int e);

/**
 * struct s_shell - a struct that conatains all our vairaible
 * @line: the cmd that user enter
 * @len: the size that should readline read
 * @read: the size that readline return after read
 * @args: two dimen array that conatine the cmds
 * pid: the proccess id when we create it with fork()
 */

struct s_shell
{
	char    *line;
	size_t  len;
	ssize_t read;
	char    **args;
	int     pid;
};

/**
 * t_shell - Typedef of struct s_shell
 */

typedef struct s_shell t_shell;

#endif /* SHELL_H */
