#include "shell.h"

/**
 * _fileno - gets the file discriptor
 * @stream: the steam to get the
 * discriptor for
 * Return: returns the discriptor
 *
 */

int _fileno(FILE *stream)
{
	int fd = -1;

	if (stream != NULL)
	{
		fd = _fcntl(fileno(stream), F_DUPFD, 0);
	}

	return (fd);

}
