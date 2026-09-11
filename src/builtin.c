#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"

int cd(const char* dest)
{
  if (dest == NULL) { dest = getenv("HOME"); }

  if (!dest)
  {
    fprintf(stderr, "cd: current user does not have a home directory\n");
    return 1;
  }

  if (chdir(dest) == -1)
  {
    perror("cd");
    return 1;
  }

  return 0;
}

