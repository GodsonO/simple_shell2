#include "shell.h"
#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static int buffer_index = 0;
static int buffer_size = 0;

ssize_t _getline(char **lineptr, size_t *n)
{
	int newline_index, i;
	if (buffer_index >= buffer_size)
	{
		buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		buffer_index = 0;

		if (buffer_size <= 0)
		{
			return (-1);
		}
	}

	newline_index = -1;
	for (i = buffer_index; i < buffer_size; i++)
	{
		if (buffer[i] == '\n')
		{
			newline_index = i;
			break;
		}
	}

	if (newline_index >= 0)
	{
		size_t line_length = newline_index - buffer_index + 1;
		*lineptr = realloc(*lineptr, line_length);

		if (*lineptr == NULL)
		{
			return (-1);
		}

		_memcpy(*lineptr, &buffer[buffer_index], line_length);
		(*lineptr)[line_length - 1] = '\0';
		*n = line_length;

		buffer_index = newline_index + 1;
		return (line_length);
	}
	else
	{
		size_t buffer_length = buffer_size - buffer_index;
		size_t current_length = *n;

		*lineptr = realloc(*lineptr, current_length + buffer_length + 1);

		if (*lineptr == NULL)
		{
			return (-1);
		}

		_memcpy(*lineptr + current_length, &buffer[buffer_index], buffer_length);
		*n +=  buffer_length;
		(*lineptr)[*n] = '\0';

		buffer_index = buffer_size;
		return buffer_length;
	}
}
