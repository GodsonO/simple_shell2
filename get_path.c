#include "shell.h"
/**
 * find_path - get the absolute path of the command
 * @filename: the cmd to get abs path of
 * Return: returns absolute path
 */

char *find_path(char *filename)
{
	char *path = _getenv("PATH");
	char *dir, *fullpath, *result = NULL;
	int path_len, name_len;

	if (path == NULL)
	{
		err_msg("Error: fetching path failed");
		return (NULL);
	}
	dir = strtok(path, ":");
	name_len = _strlen(filename);

		while (dir != NULL)
		{
			path_len = _strlen(dir);
			fullpath = malloc(path_len + name_len + 2);

			if (fullpath == NULL)
			{
				return (NULL);
			}
			_strcpy(fullpath, dir);
			_strcat(fullpath, "/");
			_strcat(fullpath, filename);

			if (access(fullpath, X_OK | F_OK) != -1)
			{
				result = fullpath;
				break;
			}
			free(fullpath);
			dir = strtok(NULL, ":");
		}

		if (result == NULL)
		{
			return (NULL);
		}

	return (result);
}
/*
int main()
{
    char *filename = "/bin/ls";
    char *path = find_path(filename);

    if (path != NULL)
    {
        printf("Absolute path of '%s': %s\n", filename, path);
        free(path);
    }
    else
    {
        printf("'%s' not found or not executable\n", filename);
    }

    return 0;
}*/
