#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void execute(char *line);

#endif
