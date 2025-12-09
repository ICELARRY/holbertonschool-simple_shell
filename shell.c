#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void execute(char *line)
{
	char *args[MAX_ARGS];
	char *token;
	int i = 0;
	pid_t pid;

	token = strtok(line, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
