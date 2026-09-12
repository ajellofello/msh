#ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
#endif

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

#include "builtin.h"
#include "alloc.h"

#define ECHO_CMD "echo"
#define EXIT_CMD "exit"
#define PWD_CMD  "pwd"
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
    if (errno != 0) { perror(CD_CMD); }
    else { fprintf(stderr, CD_CMD": HOME is unset\n"); }
    return;
  }

  int success = (chdir(dest) != -1);
  if (!success)
  {
    perror(CD_CMD);
    return;
  }

  if (shouldfree) { free(dest); }
}

void pwd_cmd(int argc, char** argv)
{
  char cwd[PATH_MAX];
  int success = (getcwd(cwd, PATH_MAX) != NULL);

  if (!success)
  {
    perror(PWD_CMD);
    return;
  }

  printf("%s\n", cwd);
}

void echo_cmd(int argc, char** argv)
{
  for (int i = 1; i < argc; i++)
    printf("%s ", argv[i]);
  printf("\n");
}

