#define _POSIX_SOURCE
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define PROMPTSIZ 1024
#define PID_CHILD 0
#define PID_ERR   -1

typedef enum { UNKNOWN, EXIT, CD } cmd_t;

static char** argv;
static char* prompt;
static int exitnum = EXIT_SUCCSS;

void terminate(int signum)
{
  free(prompt);
  free(argv);

  printf("exit\n");

  exit(exitnum);
}

int main()
{
  signal(SIGTERM, terminate);

  int running = 1;
  while (running)
  {
    prompt = getprompt(PROMPTSIZ);

    if (!prompt) { continue; }

    int argc = 0;
    argv = parse(prompt, &argc);
    char* cmd_arg = argv[0];
    cmd_t cmd = UNKNOWN;
  
    if (strcmp(cmd_arg, "exit") == 0) { cmd = EXIT; }
    else if (strcmp(cmd_arg, "cd") == 0) { cmd = CD; }
    else
    {
      fprintf(stderr, "unknown command '%s'\n", cmd_arg);
      continue;
    }

    pid_t pid = fork();
    if (pid == PID_ERR)
    {
      fprintf(stderr, "could not fork current process. Terminating Shell\n");
      exit(EXIT_FAILURE);
    }

    if (pid != PID_CHILD)
      wait(NULL);
    else
      switch (cmd)
      {
        case EXIT:
          exit_cmd(argc, argv, &exitnum); 
          break;
        case CD:
          cd_cmd(argc, argv); 
          break;
        defautl:
          exit(EXIT_FAILURE);
          break;
      }
  }

  exit(EXIT_SUCCESS);
}

