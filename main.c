#include "shell.h"

void 	build_path(t_shell *ptr, char **env)
{
	int	ret;

	ret = access(ptr->len, F_OK);
	if (ret == -1)
		perror(av[0]);
	else if (ret == 0)
		return;

}
extern char **environ;

/**
 * builtin_env - Prints the current environment.
 * Return: Always returns 0.
 */
int builtin_env(void)
{
    int i = 0;

    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return 0;
}

/**
 * init_material - init the struct with default values
 * @ptr: the addrs of the struct
 * @env: the enviremnet variable
 * @av: list of argument
 */

void	init_material(t_sehll *ptr, char **env, char **av)
{
	ptr->len = 0;
	ptr->av = av;
	build_path(ptr, env);
}

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
	t_shell	*ptr;
	ssize_t readline;
	char *line;

	ptr = malloc(sizeof(t_shell));
	init_material(ptr, env, av);
	fd_putstr("sh$ ", STDOUT_FILENO);
	readline = getline(&ptr->line, &ptr->len, stdin);
	if (readline == -1)
	{
		printf("Exiting the shell ...\n");
		return (-1);
	}
	while ((ptr->read = getline(&ptr->line, &ptr->len, stdin)) != -1)
	{
		ptr->pid = fork();
		if (ptr->pid < 0)
			perror("fork");
		if (ptr->pid == 0)
		{
			ptr->line[ptr->read - 1] = '\0'; 
			if (execve(ptr->line, ptr->args, env) == -1)
				perror(av[0]);
		}
		wait(NULL);
		fd_putstr("sh$ ", STDOUT_FILENO);
	}
	builtin_env();

	free(ptr->line);
	free(ptr);

	while ((line = custom_getline()) != NULL) {
        	printf("You entered: %s", line);
        	free(line);
	}
	return (0);
}
