#include "shell.h"

/**
 * build_path - build the path of the cmd ls => /bin/ls
 * @ptr: the pointer to the struct
 * @env: the envirment vaiable
 * Return: 0 if the path found -1 if not
 */

int	build_path(t_shell *ptr, char **env)
{
	int	ret;
	int	cmp;
	char	**check;
	char	*new_cmd;
	int	i;
	char	**path;
	char	*temp;

	i = 0;
	ptr->args = _split(ptr->line, ' ');
	ret = access(ptr->args[0], F_OK);
	if (ret == 0)
		return (0);
	while (env[i])
	{
		check = _split(env[i], '=');
		cmp = _strcmp(check[0], "PATH");
		if (cmp != 0)
			i++;
		else
		{
			new_cmd = _strdup(check[1]);
			free_split(check);
			break;
		}
		free_split(check);
	}
	if (env[i] == NULL)
		return (free_split(ptr->args), -1);
	path = _split(new_cmd, ':');
	i = 0;
	temp = _strjoin("/", ptr->args[0]);
	while (path[i])
	{
		free(ptr->line);
		ptr->line = _strjoin(path[i], temp);
		ret = access(ptr->line, F_OK);
		if (ret == 0)
			return (free_split(path), free(temp), 0);
		i++;
	}
	return (free_split(path), free(temp), -1);
}

/**
 * init_material - init the struct with default values
 * @ptr: the addrs of the struct
 * @av: list of argument
 */

void	init_material(t_shell *ptr, char **av)
{
	ptr->len = 0;
	ptr->av = av;
	ptr->args = NULL;
}

/**
 * is_built_in - function to execute the built in cmd
 * @ptr: pointer to the structur
 * @env: the envirement
 * Return: 0 if true or 1 if not
 */

int	is_built_in(t_shell *ptr, char **env)
{
	int	i;

	i = 0;
	if (_strcmp(ptr->line, "env") == 0)
	{
		while (env[i])
		{
			fd_putstr(env[i], 1);
			fd_putstr("\n", 1);
			i++;
		}
		return (0);
	}
	else if (_strcmp(ptr->line, "exit") == 0)
	{
		free(ptr->line);
		if (ptr->args)
			free_split(ptr->args);
		exit(0);
	}
	return (1);
}

/**
 * end_program - the end of the program
 * @ptr: the ponter to the struct
 * @ac: variable for nothing
 */

void	end_program(t_shell *ptr, int ac)
{
	(void)ac;
	free(ptr->line);
	if (ptr->args)
		free_split(ptr->args);
	free(ptr);
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
	t_shell	*ptr;

	ptr = malloc(sizeof(t_shell));
	init_material(ptr, av);
	while ((ptr->read = getline(&ptr->line, &ptr->len, stdin)) != -1)
	{
		if (ptr->line)
			ptr->line[_strlen(ptr->line) - 1] = '\0';
		if (is_built_in(ptr, env) == 0)
		{
			free(ptr->line);
			ptr->line = NULL;
			continue;
		}
		if (build_path(ptr, env) == -1)
		{
			fd_putstr(av[0], 2);
			fd_putstr(": command not found\n", 2);
			free(ptr->line);
			ptr->line = NULL;
			free_split(ptr->args);
			ptr->args = NULL;
			continue;
		}
		ptr->pid = fork();
		if (ptr->pid < 0)
			perror("fork");
		if (ptr->pid == 0)
		{
			if (execve(ptr->line, ptr->args, env) == -1)
				perror(av[0]);
		}
		wait(NULL);
		free_split(ptr->args);
		ptr->args = NULL;
		free(ptr->line);
		ptr->line = NULL;
	}
	end_program(ptr, ac);
	return (0);
}
