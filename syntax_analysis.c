#include"shell.h"

/**
 * syntax_analysis - analysis the tokens if they are valid
 * @tokens: the array of pointers to analysis
 * Return: 
 */
/*int syntax_analysis(char **tokens)
{
	int i, j, k, n = 1;
	char *valid_commands[] = {"exit", "cd", "mkdir"};
        int num_valid_commands = sizeof(valid_commands) / sizeof(valid_commands[0]);
        int is_valid_command = 0;
	char *valid_options[] = {"-l", "-a"};
        int num_valid_options = sizeof(valid_options) / sizeof(valid_option[0]);
        int is_valid_options = 0;

	if (tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL)
		return (0);

	for (i = 0; i < num_valid_commands; i++)
	{
		if (token[0] == '/')
		{
			if(access(token[0], F_OK) == -1)
			{
				return (0);
			}

		}
		else if (_strcmp(tokens[0], valid_commands[i]) == 0)
		{
			is_valid_command++;
			break;
		}
	}

	if (!is_valid_command)
		return (0);

	if(token[1]
	if (_strlen(tokens[1]) > 1)
	{
		for (j = 0; j < num_valid_options; j++)
		{
			if(_strstr(tokens[1], valid_options[j]) != NULL)
			{
				is_valid_options++;
				break;
			}
		}
	}
	else
	{
		for (k = 0; k < num_valid_options i++)
		{
			if (strcmp(tokens[1], valid_options[i] == 0))
			{
				is_valid_option = 1;
				break;
			}
		}
	}

	if (!is_valid_option)
		return (0);
	return 1;
}
*/
