#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void execute(char *line); /* function prototype */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}
		execute(line);
	}

	free(line);
	return (0);
}
