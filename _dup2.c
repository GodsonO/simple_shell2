#include "shell.h"

/**
 * _dup2 - duplicate file discriptor to
 * new file discriptor
 * @oldfd: old
 * @newfd: new
 * Return: result
 */
int _dup2(int oldfd, int newfd)
{
	int result;

	if (oldfd == newfd)
	{
		return (newfd);
	}
	close(newfd);

	result = _fcntl(oldfd, F_DUPFD, newfd);
	if (result == -1)
	{
		perror("Error in fcntl");
		return (-1);
	}
	return (result);
}
