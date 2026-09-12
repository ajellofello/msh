#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

int main()
{
  int shouldexit = 0;

  while (!shouldexit)
  {
    char* prompt = getprompt(PROMPTSIZ);

    int argc = 0;
    char** argv = parse(prompt, &argc);

    printf("argc: %d\n", argc);
    printf("argv: ( ");
    for (int i = 0; i < argc; i++)
      printf("\"%s\" ", argv[i]);
    printf(")\n");

    shouldexit = (strcmp(prompt, "exit") == 0);
  }
  printf("exit\n");

  return 0;
}

