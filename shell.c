#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

void execute(char *line)
{
	char *args[64];
	char *token;
	pid_t pid;
	int i = 0;

	token = strtok(line, " \t\n");
	while (token != NULL && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	else
		wait(NULL);
}
