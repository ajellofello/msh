#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

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
  
    if (strcmp(cmd, "exit") == 0) { exit_cmd(argc, argv); }
    else if (strcmp(cmd, "cd") == 0) { cd_cmd(argc, argv); }
    else if (strcmp(cmd, "pwd") == 0) { pwd_cmd(argc, argv); }
    else if (strcmp(cmd, "echo") == 0) { echo_cmd(argc, argv); }
    else
    {
      fprintf(stderr, "unknown command '%s'\n", cmd);
      continue;
    }

    free(argv);
    free(prompt);
  }

  exit(EXIT_SUCCESS);
}

