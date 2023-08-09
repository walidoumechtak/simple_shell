#include "shell.h"

/**
 * main - the start of the program
 * @ac: the length of the argv
 * @av: array of arguments
 * @env: the envirement
 * Return: the exit status of the shell
 */

int	main(int ac, char **av, char **env)
{
	(void)ac;
	char	*line;
	size_t	len;
	ssize_t	read;
	char	*args[] = {"sh", NULL};
	int	pid;

	len = 0;
	fd_putstr("sh$ ", STDOUT_FILENO);
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		pid = fork();
		if (pid < 0)
			perror("fork");
		if (pid == 0)
		{
			line[read - 1] = '\0'; 
			if (execve(line, args, env) == -1)
				perror(av[0]);
		}
		wait(NULL);
		fd_putstr("sh$ ", STDOUT_FILENO);
	}
	free(line);
	return (0);
}
