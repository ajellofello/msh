#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

static char** argv;
static char* prompt;
static int exit_code = 0;

void terminate(int signum)
{
  free(prompt);
  free(argv);

  printf(ANSI_ITALIC"exit\n"ANSI_RESET);
  exit(exit_code);
}

int main()
{
  int shouldexit = 0;

  while (!shouldexit)
  {
    prompt = getprompt(PROMPTSIZ);

    int argc = 0;
    argv = parse(prompt, &argc);

    printf("argc: %d\n", argc);
    printf("argv: ( ");
    for (int i = 0; i < argc; i++)
      printf("\"%s\" ", argv[i]);
    printf(")\n");

    shouldexit = (strcmp(prompt, "exit") == 0);
  }

  free(prompt);
  free(argv);

  return 0;
}

