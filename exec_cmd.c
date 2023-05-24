#include "shell.h"

/**
 * 
 *
 */

void exec_cmnd(char **command)
{
	int status;
	int exit_status;

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("i am inside child");
		if (_execvp(command[0], command) == -1)
		{
			perror("_execve");
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(1);
		}
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			printf("Command exited with status: %d\n", exit_status);
		}
		else
		{
			printf("command did not exit normally\n");
		}
	}
}
