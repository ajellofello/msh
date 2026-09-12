#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#include "builtin.h"

#define EXIT_CMD "exit"
#define CD_CMD   "cd"

int exit_cmd(int argc, char** argv, int* exitnum, pid_t ppid)
{
  char* exitstat_str = (argv[1]) ? argv[1] : NULL;

  if (!exitstat_str)
  {
    *exitnum = 0;
    kill(ppid, SIGTERM);
  }

  char c;
  for (int i = 0; (c = exitstat_str[i]); i++)
  {
    if (!isdigit(c) && c != '-')
    {
      fprintf(stderr, EXIT_CMD": expected a numeric exit status\n");
      return 1;
    }
  }

  *exitnum =  atoi(exitstat_str);
  kill(ppid, SIGTERM);
}

int cd_cmd(int argc, char** argv)
{
  char* dest = (argv[1]) ? dest : getenv("HOME");

  if (!dest)
  {
    fprintf(stderr, CD_CMD": current user does not have a home directory\n");
    return 1;
  }

  int success = (chdir(dest) != -1);
  if (!sucess)
  {
    perror("cd");
    return 1;
  }

  return 0;
}

