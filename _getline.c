#include "shell.h"

#define BUFFER_SIZE 1024



static int buffer_index;
static int buffer_size;
static char buffer[BUFFER_SIZE];

static ssize_t read_buffer(FILE *stream);
static int find_newline_index(void);
static ssize_t process_line(char **lineptr, size_t *n, int newline_index);
static ssize_t process_buffer(char **lineptr, size_t *n);

/**
 * read_buffer - reads from screen
 * @stream: the stream to read
 * Return: buffer_size
 */
static ssize_t read_buffer(FILE *stream)
{
	buffer_size = read(_fileno(stream), buffer, BUFFER_SIZE);
	buffer_index = 0;

	if (buffer_size <= 0)
	{
		return (-1);
	}

	return (buffer_size);
}
/**
 * find_newline_index - to know the index of current command argument
 * Return: void
 */

static int find_newline_index(void)
{
	int i;

	for (i = buffer_index; i < buffer_size; i++)
	{
		if (buffer[i] == '\n')
		{
			return (i);
		}
	}

	return (-1);
}
/**
 * process_line - checks the argument read from the command line
 * @lineptr: pointer to a pointer char
 * @n: size of char
 * @newline_index: contains newline_index
 * Return: line_length
 */

static ssize_t process_line(char **lineptr, size_t *n, int newline_index)
{
	size_t line_length = newline_index - buffer_index + 1;

	if (line_length > *n)
	{
		*lineptr = realloc(*lineptr, line_length);
		*n = line_length;
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	_memcpy(*lineptr, &buffer[buffer_index], line_length);
	(*lineptr)[line_length - 1] = '\0';

	buffer_index = newline_index + 1;
	return (line_length);
}
/**
 * process_buffer - read many chars at once and calls
 * the least possible the read system call
 * @lineptr: pointer to a char pointer
 * @n: size of char
 * Return: buffer_length
 */
static ssize_t process_buffer(char **lineptr, size_t *n)
{
	size_t buffer_length = buffer_size - buffer_index;
	size_t current_length = *n;

	*lineptr = realloc(*lineptr, current_length + buffer_length + 1);

	if (*lineptr == NULL)
	{
		return (-1);
	}

	_memcpy(*lineptr + current_length, &buffer[buffer_index], buffer_length);
	*n += buffer_length;
	(*lineptr)[*n] = '\0';

	buffer_index = buffer_size;
	return (buffer_length);
}
/**
 * _getline - reads an entire line from screen
 * @lineptr: stores the address of the buffer
 * @n: stores address of the newline character
 * @stream: conitains the string
 * Return: the number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int newline_index;

	if (buffer_index >= buffer_size)
	{
		if (read_buffer(stream) <= 0)
		{
			return (-1);
		}
	}
	newline_index = find_newline_index();
	if (newline_index >= 0)
	{
		return (process_line(lineptr, n, newline_index));
	}
	else
	{
		return (process_buffer(lineptr, n));
	}
}
