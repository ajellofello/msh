#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

extern int laststatus; /* represents the exit status of the last command. Defined in src/shell.c */

int main()
{
  int running = 1;
  while (running)
  {
    char* prompt = getprompt(PROMPTSIZ);

    if (!prompt) { continue; }

    int argc = 0;
    char** argv = parse(prompt, &argc);
    char* cmd = argv[0];

    laststatus = exec(cmd, argc, argv);

    free(argv);
    free(prompt);
  }

  exit(EXIT_SUCCESS);
}

