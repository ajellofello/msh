#ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>

#include "builtin.h"
#include "alloc.h"

#define EXIT_CMD "exit"
#define CD_CMD   "cd"

void exit_cmd(int argc, char** argv)
{
  char* exitstat = (argv[1]) ? argv[1] : NULL;

  if (!exitstat)
  {
    printf("exit\n");
    exit(EXIT_SUCCESS);
  }

  char c;
  for (int i = 0; (c = exitstat[i]); i++)
  {
    if (!isdigit(c) && c != '-')
    {
      fprintf(stderr, EXIT_CMD": expected a numeric exit status\n");
      return;
    }
  }

  printf("exit\n");
  exit(atoi(exitstat));
}

void cd_cmd(int argc, char** argv)
{
  int shouldfree = (argv[1] != NULL); /* if a path was given we need to free the resulted realpath() */
  char* dest = (argv[1]) ? realpath(argv[1], NULL) : getenv("HOME");

  if (!dest)
  {
    fprintf(stderr, CD_CMD": HOME is unset\n");
    return;
  }

  int success = (chdir(dest) != -1);
  if (!success)
  {
    perror("cd");
    return;
  }

  if (shouldfree) { free(dest); }
}

