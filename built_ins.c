#include "shell.h"

/**
 *
 *
 */

void my_exit(char **arg)
{
	if (arg[1] != NULL)
	{
		int exit_code;
		exit_code = _atoi(arg[1]);
		exit(exit_code);
	}
	else
	{
		exit(0);
	}
}
/**
 *
 *
 */
void _env()
{
	_printenv();
}
/**
 *
 *
 */
/*
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len;
	size_t value_len;
	size_t env_size;
	char *env_var;
	char *env_str;

	if (name == NULL || value == NULL)
	{
		return (-1);
	}

	env_var = _getenv(name);
	if (env_var != NULL && overwrite == 0)
	{
		return (0);
	}

	name_len = _strlen(name);
	value_len = _strlen(value);
	env_size = name_len + 1 + value_len + 1;

	env_str = (char *) malloc (env_size);
	if (env_str == NULL)
	{
		return (-1);
	}

	_strcpy(env_str, name);
	env_str[name_len] = '=';
	_strcpy(env_str + name_len + 1, value);

	if (_putenv(env_str) != 0)
	{
		free(env_str);
		return (-1);
	}
	return (0);
}

*/
/*int _unsetenv(const char *name)
{
	if (name == NULL)
	{
		return (-1);
	}

	if (un

*/
