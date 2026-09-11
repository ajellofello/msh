#include <string.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024

int main()
{
  char* prompt;

  while ((prompt = getprompt(PROMPTSIZ)))
  {
    int shouldexit = (strcmp(prompt, "exit") == 0);
    if (shouldexit)
    {
      puts("exit");
      break;
    }
    
    int argc = 0;
    char** argv = parse(prompt, &argc);

    printf("argc: %d\n", argc);
    printf("argv: ( ");
    for (int i = 0; i < argc; i++)
      printf("\"%s\" ", argv[i]);
    printf(")\n");
  }

  return 0;
}

