#include "shell.h"

#define MAX_COMMAND_LENGTH 1024

void execute_piped_commands(char *command1, char *command2);
/**
 * non_int_execute_command - execute
 * command
 * @command: the command
 * Return: return the status of program
 *
 */
int non_int_execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[MAX_COMMAND_LENGTH];
	int i = 0;

	char *token = _strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " ");
	}
	args[i] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		_execvp(args[0], args);
		perror("_execvp");
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}
