#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

#define ANSI_RESET "\e[0m"
#define ANSI_CYAN  "\e[0;36m"
#define PROG       "msh"

char* getprompt(const size_t size);
char** parse(char* prompt, int* argc);
void exec(char* path, char** argv);

#endif

