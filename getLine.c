#include "shell.h"
/**
 * custom_getline - reads an entire line from screen
 * @lineptr: stores the address of the buffer
 * @n: stores address of the newline character
 * @stream: conitains the string
 * Return: the number of characters read
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bufsize = *n, i = 0;
	ssize_t bytesRead;

	if (lineptr == NULL || n == NULL)
	{
		perror("Invalid arguments");
		return (-1);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(bufsize);
		if (*lineptr == NULL)
		{
			perror("Memory allocation failed");
			return (-1);
		}
	}
	while ((bytesRead = read(fileno(stream), &(*lineptr)[i], 1)) > 0)
	{
		if ((*lineptr)[i] == '\n')
			break;
		i++;
		if (i >= bufsize - 1)
		{
			bufsize += *n - 1;
			char *newptr = realloc(*lineptr, bufsize);

			if (newptr == NULL)
			{
				perror("Memory reallocation failed");
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			*lineptr = newptr;
		}
	}
	if (bytesRead == -1)
	{
		perror("Read error");
		free(*lineptr);
		*lineptr = NULL;
		return (-1);
	}
	(*lineptr)[i] = '\0';
	if (bytesRead == 0 && i == 0)
	{
		free(*lineptr);
		*lineptr = NULL;
		return (-1);
	}
	return (i);
}
