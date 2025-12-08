#include "shell.h"

/**
 * execute - executes a command
 * @line: input command
 */
void execute(char *line)
{
	pid_t pid;
	char *argv[2];
	int status;

	line[strcspn(line, "\n")] = '\0';
	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}
