#ifndef BUILTIN_H
#define BUILTIN_H

#include <sys/types.h>

void cd_cmd(int argc, char** argv);
void exit_cmd(int argc, char** argv, int* exitnum);

#endif
