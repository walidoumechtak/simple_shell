#include "shell.h"

#define buff_size 1024


/**
 * custom_getline - it's a custom function thet get us the implementation of getline.
 * Return: Pointer to the read line or NULL on failure or end of file.
 */

char *custom_login(void)
{
	static char buff[buff_size];
	static size_t buff_pos = 0;
	static ssize_t buff_read = 0;
	char *line = 0;
	size_t line_size = 0;
	ssize_t bytes_read = 0;

	do
	{
    		if (buff_pos >= buff_read)
		{
			buff_read = read(STDIN_FILENO, buff, buff_size);
			buff_pos = 0;
			if (buff_read == 0)
				return NULL;
		}
		if (line_size <= 0)
		{
			line_size = buff_size;
			line = malloc(line_size);
			if (!line)
				return NULL;
		}
		
		line[bytes_read] = buff[buff_pos];
		bytes_read++;
		buffer_pos++;
		if (line_size <= bytes_read)
		{
			line_size += buff_size;
			line = realloc(line, line_size);
			if (!line)
				return NULL;
		}
	}while(1);
	line[bytes_read] = '\0';
	return line
}
