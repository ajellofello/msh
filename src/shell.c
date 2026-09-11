#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "shell.h"

#define ANSI_RESET "\e[0m"
#define ANSI_BLUE  "\e[0;34m"
#define BASE_ARGV 8

void* xmalloc(const size_t size)
{
  void* mem = malloc(size);

  if (!mem)
  {
    perror("malloc");
    exit(1);
  }
  return mem;
}

void* xcalloc(size_t n, size_t size)
{
  void* mem = calloc(n, size);

  if (!mem)
  {
    perror("calloc");
    exit(1);
  }
  return mem;
}

void* xrealloc(void* p, size_t size)
{
  void* mem = realloc(p, size);

  if (!mem)
  {
    perror("realloc");
    exit(1);
  }
  return mem;
}

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

  printf(ANSI_BLUE"msh$ "ANSI_RESET);
  fgets(prompt, size, stdin);

  rm_trailingnl(prompt);
  strip(&prompt);
  return prompt;
}

char** parse(char* prompt, int* argc)
{
  size_t size = BASE_ARGV;
  char** argv = xcalloc(size, sizeof(char*));
  char* tok = strtok(prompt, " ");

  do
  {
    if (sizeof(argv) <= *argc)
      xrealloc(argv, (size += 8));

    argv[*argc] = tok;

    (*argc)++;
  } while ((tok = strtok(NULL, " ")));

  argv[*argc] = NULL;
  return argv;
}

