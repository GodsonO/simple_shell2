#include "shell.h"

/**
 * parse - to
 * @token: 
 * @ac: a
 * @av; v
 */
void parse(char **token, int ac, char *av[])
{
	int j = 1;
	char *command = token[0];


	switch(token[0])
	{
		case "exit":
			printf("am exiting");
			break;
		case "cd":
			printf("am changing directories");
			break;
		case "echo":
			printf("i am echoing");
			break;
		case "alias":
			printf("i am alias");
			break;
		case "unalias":
			printf("i am unalias");
			break;
		case "pwd":
			printf("i am pwd");
			break;
		default:
			if (valid_cmd(command) == 0)
			{
				if (command[0][0] == '/')
				{
					//execute(token);
				}
				else
				{
					//path = get_path(token[0]);
					//token[0] = path
					//execute(token);
				}
				break;
			}
			else
			{
				err_msg("%s:", av[0]);
				_putchar(j);
				err_msg(" %s: not found\n", j, token[0]);
				j++;
			}
	}
}
int valid_cmd(const char *command)
{
	if (access(command, F_OK | X_OK) != -1)
	{
		printf("command is valid");
		return (0);
	}
}
