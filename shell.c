#include "shell.h"

/**
 * execute - Runs a command with arguments
 * @line: input string from user
 */
void execute(char *line)
{
	char *args[64];
	int i = 0, status;
	pid_t pid;

	args[i] = strtok(line, " \t\n");
	while (args[i] != NULL && i < 63)
	{
		i++;
		args[i] = strtok(NULL, " \t\n");
	}

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork failed");
}
