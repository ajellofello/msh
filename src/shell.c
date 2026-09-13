#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "shell.h"
#include "alloc.h"

#define BASE_ARGV 8
#define PID_CHILD 0
#define PID_ERROR -1

/* The exit status of the last command */
int laststatus = 0;

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

  if (laststatus != 0)
    printf(ANSI_RED"$ "ANSI_RESET);
  else
    printf(ANSI_CYAN"$ "ANSI_RESET);

  fgets(prompt, size, stdin);

  rm_trailingnl(prompt);
  strip(&prompt);

  if (strcmp(prompt, "") == 0) { return NULL; }

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

void exec(char* path, char** argv)
{
  const pid_t pid = fork();

  if (pid == PID_ERROR)
  {
    fprintf(stderr, PROG": could not fork current process. Shell exiting\n");
    perror(PROG": fork");
    exit(EXIT_FAILURE);
  }

  if (pid != PID_CHILD)
    wait(NULL);
  else
  {
    int success = (execvp(path, argv) != -1);

    if (!success)
    {
      perror(PROG);
      exit(EXIT_FAILURE);
    }
  }
}


