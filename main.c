#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ---- COLORS ---- */
#define ANSI_RESET "\e[0m"
#define ANSI_BLUE  "\e[0;34m"
/* ---------------- */

#define PROMPTSIZ  1024

void* xmalloc(size_t size)
{
  void* mem = malloc(size);

  if (!mem)
  {
    perror("malloc");
    exit(1);
  }

  return mem;
}

char* getprompt()
{
  char* prompt = xmalloc(PROMPTSIZ);

  printf(ANSI_BLUE"msh$ "ANSI_RESET);
  fgets(prompt, PROMPTSIZ, stdin);

  return prompt;
}

void rm_trailingnl(char* str)
{
  size_t end = (strlen(str) - 1);
  str[end] = (str[end] == '\n') ? '\0' : str[end];
}

int main()
{
  char* prompt;

  while ((prompt = getprompt()))
  {
    rm_trailingnl(prompt);

    int shouldexit = (strcmp(prompt, "exit") == 0);
    if (shouldexit)
    {
      puts("exit");
      break;
    }
  }

  return 0;
}

