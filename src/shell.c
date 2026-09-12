#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "shell.h"
#include "alloc.h"

#define BASE_ARGV 8

void rm_trailingnl(char* str)
{
  if (str == NULL) { return; }

  size_t end = (strlen(str) - 1);
  str[end] = (str[end] == '\n') ? '\0' : str[end];
}

void lstrip(char** str)
{
  if (str == NULL) { return; }

  while (**str == ' ')
    ++(*str);
}

void rstrip(char* str)
{
  if (str == NULL) { return; }

  for (int i = (strlen(str) - 1); i > 0; i--)
  {
    if (str[i] != ' ')
    {
      str[i + 1] = '\0';
      break;
    }
  }
}

void strip(char** str)
{
  lstrip(str);
  rstrip(*str);
}

char* getprompt(const size_t size)
{
  char* prompt = xmalloc(size);

  printf(ANSI_CYAN"$ "ANSI_RESET);
  fgets(prompt, size, stdin);

  rm_trailingnl(prompt);
  strip(&prompt);
  return prompt;
}

char** parse(char* prompt, int* argc)
{
  size_t cap = BASE_ARGV;
  char** argv = xcalloc(cap, sizeof(char*));
  char* tok = strtok(prompt, " ");

  do
  {
    if (cap <= *argc)
      xrealloc(argv, ((cap += 8) * sizeof(char*)));

    argv[*argc] = tok;

    (*argc)++;
  } while ((tok = strtok(NULL, " ")));

  argv[*argc] = NULL;
  return argv;
}

