#include "shell.h"

/**
 * count_word - funct that calc how many word in string
 * @str: the string
 * Return: the result as int
 */

int	coutn_word(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
		{
			res++;
			while (str[i] != ' ' && str[i] != '\t')
				i++;
		}
		i++;
	}
	return (res);
}

/**
 * _split - function that split a string and return an array of it
 * @str: the string should be splited
 * @c: the separator
 * Return: two dimension array
 */

char	**_split(char *str, char c)
{
	char	**arr;
	int	i;
	int	s;
	int	e;

	i = 0;
	arr = malloc(sizeof(char *) * cout_word(str));
}
