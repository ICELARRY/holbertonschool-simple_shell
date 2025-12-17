#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

extern char **environ;

void execute(char *line)
{
	char *args[64];
	char *token;
	int i = 0;
	pid_t pid;

	token = strtok(line, " \t\n");
	while (token && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	/* Handle PATH resolution if needed */

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
