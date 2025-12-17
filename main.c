#include "shell.h"

/**
 * main - Entry point of the shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		write(1, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			write(1, "\n", 1);
			break;
		}

		execute(line);
	}
	free(line);
	return (0);
}
