#include "shell.h"

/**
 * parse - to
 * @token: 
 * @ac: a
 * @av; v
 */
void execute(char **token, int ac, char *av[])
{
	char *command = token[0];

	(void) ac;
	(void) av;
	(void) command;


	if (_strcmp((token[0]), "exit"))
	{
		printf("am exiting\n");
		my_exit(token);
	}
	else if (_strcmp((token[0]), "cd"))
	{
		printf("am changing directories");
	}
	else if (_strcmp((token[0]), "echo"))
	{
		printf("i am echoing");
	}
	else if(_strcmp((token[0]), "alias"))
	{
		printf("i am alias");
	}
	else if(_strcmp((token[0]), "unalias"))
	{
		printf("i am unalias");
	}
	else if (_strcmp((token[0]), "env"))
	{
		printf("i am env\n");
		_env();
	}
	else
	{
		err_msg("bultin function not found\n");
	}

}
/*
int valid_cmd(const char *command)
{
	if (access(command, F_OK | X_OK) != -1)
	{
		printf("command is valid");
		return (0);
	}
}*/
