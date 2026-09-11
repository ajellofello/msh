#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

char* getprompt(const size_t size);
char** parse(char* prompt, int* argc);

#endif

