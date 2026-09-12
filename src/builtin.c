#define _POSIX_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#include "builtin.h"

#define EXIT_CMD "exit"
#define CD_CMD   "cd"

extern char** argv;
extern char* prompt;

void free_and_terminate(int exitnum)
{
  free(prompt);
  free(argv);

  exit(exitnum);
}

void exit_cmd(int argc, char** argv, int* exitnum)
{
  const pid_t ppid = getppid();
  char* exitstat_str = (argv[1]) ? argv[1] : NULL;

  if (!exitstat_str)
  {
    *exitnum = 0;
    kill(ppid, SIGTERM);
    free_and_terminate(EXIT_SUCCESS);
  }

  char c;
  for (int i = 0; (c = exitstat_str[i]); i++)
  {
    if (!isdigit(c) && c != '-')
    {
      fprintf(stderr, EXIT_CMD": expected a numeric exit status\n");
      free_and_terminate(EXIT_FAILURE);
    }
  }

  *exitnum =  atoi(exitstat_str);
  kill(ppid, SIGTERM);
  free_and_terminate(EXIT_SUCCESS);
}

void cd_cmd(int argc, char** argv)
{
  const char* dest = (argv[1]) ? argv[1] : getenv("HOME");

  if (!dest)
  {
    fprintf(stderr, CD_CMD": current user does not have a home directory\n");
    exit(EXIT_FAILURE);
  }

  int success = (chdir(dest) != -1);
  if (!success)
  {
    perror("cd");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

