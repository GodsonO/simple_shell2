#include "shell.h"

/**
 * my_exit - exit a shell
 * @arg: the argument
 * Return: void
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
 * _env - env
 * Return: void
 */
void _env(void)
{
	_printenv();
}
