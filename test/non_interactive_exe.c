#include"shell.h"

/**
 *
 *
 */
int exec_cmd(char **arg, int ac, char *av[])
{
	int i, j, len = 0;

	for (j = 0; arg[j] != NULL; j++)
	{
		len++;
	}
	for (i = 1; arg[i] != NULL; i++)
	{
		if (arg[i] == "<")
		{
			printf("i am handling input redirction");
			redirection(arg[i], arg, i); 
		}
		else if (arg[i] == ">")
		{
			printf("i am handling output redirection");
		}
		else if (arg[i] == ">>")
		{
			printf("i am handiling output redirctioon appending");
		}
