#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"

#define CD_CMD "cd"

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

