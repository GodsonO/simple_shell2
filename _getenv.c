#include "shell.h"

extern char **environ;
/**
 * _getenv - gets the directoris in
 * environment varibles
 * @name: name of the environment variable
 * Return: returns NULL is failed and
 * directories if successful
 */
char *_getenv(const char *name)
{
	size_t len;
	char **ep;

	if (name == NULL)
	{
		return (NULL);
	}

	len = _strlen(name);
	ep = environ;

	while (*ep != NULL)
	{
		if (*ep != NULL && _strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
		{
			return (*ep);
		}
		ep++;
	}
	return (NULL);
}
