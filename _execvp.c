#include "shell.h"

/**
 * _execvp - it search for cmd in PATH
 * and execute it
 * @cmd: the cmd to search in PATH
 * @arguments: the arguments of the cmd
 * Return: returns 0 if successful and -1 for failure
 *
 */

int _execvp(const char *cmd, char *const arguments[])
{
	char *path_copy;
	char *dir;
	char *path = _getenv("PATH");
	char *path_separator = _strchr(cmd, '/');

	if (path_separator != NULL)
	{
		execve(cmd, arguments, environ);
		perror("execve");
		return (-1);
	}
	if (path == NULL)
	{
		print_err("Error: PATH environment variable not set.\n");
		return (-1);
	}

	path_copy = _strdup(path);
	dir = _strtok(path_copy, ":");

	while (dir != NULL)
	{
		char program_path[256];
		_strncpy(program_path, dir, sizeof(program_path));
		_strncat(program_path, "/", sizeof(program_path) - _strlen(program_path) - 1);
		_strncat(program_path, cmd, sizeof(program_path) - _strlen(program_path) - 1);

		execve(program_path, arguments, environ);

		dir = _strtok(NULL, ":");
	}

	print_err("Error: Program '%s' not found in PATH.\n", cmd);
	free(path_copy);

	return (-1);
}
int main() {
    const char *cmd = "ls";
    char *const arguments[] = {"ls", "-l", NULL};

    int result = _execvp(cmd, arguments);

    if (result == -1) {
        printf("Execution failed.\n");
    }

    return 0;
}
