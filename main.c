#include "shell.h"

int	build_path(t_shell *ptr, char **env)
{
	int	ret;
	char	*new_cmd;
	int	i;
	char	**path;
	char	*temp;

	i = 0;
	ptr->args = _split(ptr->line, ' ');
	ret = access(ptr->line, F_OK);
	if (ret == -1)
	{
		free_split(ptr->args);
		free(ptr->line);
		return (-1);
	}
	else if (ret == 0)
		return (0);
	while (env[i])
	{
		new_cmd = _strstr(env[i], "PATH");
		if (!new_cmd)
			i++;
		else
			break;
	}
	if (env[i] == NULL) // the PATH variable not found
		return (free_split(ptr->args), -1);
	path = _split(new_cmd + 5, ':');
	i = 0;
	while (path[i])
	{
		ret = access(path[i], F_OK);
		if (ret == -1)
			return (free_split(path), free(ptr->line), -1);
		else if (ret == 0)
		{
			temp = _strjoin(path[i], ptr->line);
			free(ptr->line);
			ptr->line = temp;
			return (free_split(path), 0);
		}
		i++;
	}
	return (-2);
}

/**
 * init_material - init the struct with default values
 * @ptr: the addrs of the struct
 * @env: the enviremnet variable
 * @av: list of argument
 */

void	init_material(t_shell *ptr, char **env, char **av)
{
	(void)env;
	ptr->len = 0;
	ptr->av = av;
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

		if (build_path(ptr, env) == -1)
		{
			perror(av[0]);
			free(ptr->line);
			continue;
		}
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
		free_split(ptr->args);
		fd_putstr("sh$ ", STDOUT_FILENO);
	}
	free(ptr->line);
	free(ptr);
	return (0);
}
