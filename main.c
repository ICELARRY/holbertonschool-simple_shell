#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] != '\n')
			execute(line);
	}
	free(line);
	return (0);
}
