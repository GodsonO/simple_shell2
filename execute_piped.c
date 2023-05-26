#include "shell.h"
/**
 * execute_piped_commands - execute piped commads
 * @command1: first command
 * @command2: second command
 */
void execute_piped_commands(char *command1, char *command2)
{
	int pipefd[2];
	pid_t pid_one, pid2;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid_one = fork();
	if (pid_one == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid_one == 0)
	{
		close(pipefd[0]);
		_dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		non_int_execute_command(command1);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid2 == 0)
	{
		close(pipefd[1]);
		_dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		non_int_execute_command(command2);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_one, NULL, 0);
	waitpid(pid2, NULL, 0);
}
