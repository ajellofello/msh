#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

extern int laststatus; /* represents the exit status of the last command. Deined in src/shell.c */

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

    if (strcmp(cmd, "help") == 0)
    {
      HELP();
      laststatus = EXIT_SUCCESS; /* as HELP() can't fail */
      continue;
    }

    if (strcmp(cmd, "exit") == 0) { laststatus = exit_cmd(argc, argv); }
    else if (strcmp(cmd, "cd") == 0) { laststatus = cd_cmd(argc, argv); }
    else if (strcmp(cmd, "pwd") == 0) { laststatus = pwd_cmd(argc, argv); }
    else if (strcmp(cmd, "echo") == 0) { laststatus = echo_cmd(argc, argv); }
    else
      exec(cmd, argv);

    free(argv);
    free(prompt);
  }

  exit(EXIT_SUCCESS);
}

