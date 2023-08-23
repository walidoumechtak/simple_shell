#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    fd_putstr(char *str, int fd);
char    *_substr(char *str, int s, int e);
char	*_strdup(char *str);
int	_strlen(char *str);
void    free_split(char **arr);
char	*_strjoin(char *s1, char *s2);
char	**_split(char *str, char c);
char	*_strstr(char *str, char *needed);
int	_strcmp(char *s1, char *s2);

/**
 * struct s_shell - a struct that conatains all our vairaible
 * @av: the argument av for the main func
 * @line: the cmd that user enter
 * @len: the size that should readline read
 * @read: the size that readline return after read
 * @args: two dimen array that conatine the cmds
 * @pid: the proccess id when we create it with fork()
 */

struct s_shell
{
	char	**av;
	char    *line;
	size_t  len;
	ssize_t read;
	char    **args;
	int     pid;
	int	exit_s;
};

/* t_shell - Typedef of struct s_shell */

typedef struct s_shell t_shell;

int	build_path(t_shell *ptr, char **env);

#endif /* SHELL_H */
