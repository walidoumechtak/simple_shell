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

	ptr = malloc(sizeof(t_shell));
	init_material(ptr, env, av);
	fd_putstr("sh$ ", STDOUT_FILENO);
	while ((ptr->read = getline(&ptr->line, &ptr->len, stdin)) != -1)
	{
		/*
		 * Your code should be here env() and exit() 
		 */

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
	free(ptr->line);
	free(ptr);
	return (0);
}
