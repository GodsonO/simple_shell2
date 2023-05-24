#include "shell.h"

/**
 *
 *
 */
int is_valid_command(const char *token)
{
	size_t i, j;
	const char *valid_commands[] = {"mdkdr", "cd"};
	const char *valid_options[] = {"-l", "-r", "-a"};

	for (i = 0; i < sizeof(valid_commands) / sizeof(valid_commands[0]); i++)
	{
		if (_strcmp(valid_commands[i], token) == 0)
		{
			return (1);
		}
	}

	for (j = 0; j < sizeof(valid_options) / sizeof(valid_options[0]); j++)
	{
		if (_strcmp(valid_options[i], token) == 0)
		{
			return (1);
		}
	}

	return (0);
}

int is_executable(const char *command)
{
	return (access(command, X_OK | F_OK ) == 0);
}

void execute_env()
{
	extern char **env;
	printf("Environment variables: \n");

	for (env = environ; *env != NULL; env++)
	{
		print("%s\n", *env);
	}
}

void execute_cd(const char *path)
{
	if (chdir(path) != 0)
	{
		print("Error: failed to change dirctory - %S\n", path);
	}
	else
	{
		print("changed dirctory to - %s\n", path);
	}
}

void interpret_command(char **tokens, int num_tokens)
{
	if (!is_valid_command(tokens[0]))
	{
		print("Error: Invalid command - %s\n", tokens[0]);
		return;
	}

	if (
