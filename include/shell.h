#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

#define ANSI_ITALIC  "\e[3m"
#define ANSI_RESET   "\e[0m"
#define ANSI_CYAN    "\e[0;36m"

char* getprompt(const size_t size);
char** parse(char* prompt, int* argc);

#endif

