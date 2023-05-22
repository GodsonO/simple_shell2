#include "shell.h"

/**
 * free_token - free the pointer array
 * @token: the memory space to free
 */

void free_token(char **token)
{
	size_t i;

	if (token == NULL)
	{
		return;
	}

	for (i = 0; token[i] != NULL; i++)
	{
		free(token[i]);
	}

	//free(token);
}
