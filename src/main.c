#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCSS  0
#define PROMPTSIZ    1024
#define PID_CHILD    0
#define PID_ERR      -1
#define PROG         "msh"

static char** argv;
static char* prompt;
static int exitnum = EXIT_SUCCSS;

void terminate(int signum)
{
  free(prompt);
  free(argv);

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

    char* cmd = argv[0];

    pid_t pid = fork();

    if (pid == PID_ERR)
    {
      fprintf(stderr, PROG": could not fork current process. Terminating Shell\n");
      exit(EXIT_FAILURE);
    }

    if (pid != PID_CHILD)
    {
      pid_t terminated = wait(NULL);
    }
    else
    {
      if (strcmp(cmd, "exit") == 0) { exit_cmd(argc, argv, &exitnum); }
      else if (strcmp(cmd, "cd") == 0) { cd_cmd(argc, argv); }
    }
  }

  exit(EXIT_SUCCESS);
}

