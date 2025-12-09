#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

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

	if (strchr(args[0], '/') == NULL)
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		while (dir)
		{
			char *full_path = malloc(strlen(dir) + strlen(args[0]) + 2);
			sprintf(full_path, "%s/%s", dir, args[0]);

			if (access(full_path, X_OK) == 0)
			{
				args[0] = full_path;
				break;
			}
			free(full_path);
			dir = strtok(NULL, ":");
		}
		free(path_copy);

		if (!dir)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			return;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		if (strchr(args[0], '/') == NULL)
			free(args[0]);
	}
}
