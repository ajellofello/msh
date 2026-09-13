#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "builtin.h"
#include "shell.h"
#include "alloc.h"

#define BASE_ARGV 8
#define PID_CHILD 0
#define PID_ERROR -1
#define UNKNOWN   -1

/* The exit status of the last command */
int laststatus = EXIT_SUCCESS;

void rm_trailingnl(char* str)
{
  if (str == NULL) { return; }

  size_t end = (strlen(str) - 1);
  str[end] = (str[end] == '\n') ? '\0' : str[end];
}

char* getprompt(const size_t size)
{
  char* prompt = xmalloc(size);

  if (laststatus != EXIT_SUCCESS)
    printf(ANSI_RED"$ "ANSI_RESET);
  else
    printf(ANSI_CYAN"$ "ANSI_RESET);
  fflush(stdout);

  fgets(prompt, size, stdin);

  rm_trailingnl(prompt);

  if (strcmp(prompt, "") == 0)
  {
    free(prompt);
    return NULL;
  }

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

int execbuiltin(char* cmd, int argc, char** argv)
{
  if (strcmp(cmd, "help") == 0)
  {
    HELP();
    return EXIT_SUCCESS;
  }

  if (strcmp(cmd, "exit") == 0) { return exit_cmd(argc, argv); }
  if (strcmp(cmd, "cd") == 0) { return cd_cmd(argc, argv); }
  if (strcmp(cmd, "pwd") == 0) { return pwd_cmd(argc, argv); }
  if (strcmp(cmd, "echo") == 0) { return echo_cmd(argc, argv); }

  return UNKNOWN; /* its safe to return UNKNOWN (-1) here even though technically any of
                   * the builtins but HELP() could return that as an exit status, but since
                   * all builtins return only EXIT_SUCCESS (0) and EXIT_FAILURE (1) its fine
                   */
}

int execextern(char* path, int argc, char** argv)
{
  const pid_t pid = fork();

  if (pid == PID_ERROR)
  {
    fprintf(stderr, PROG": could not fork current process\n");
    perror(PROG": fork");
    exit(EXIT_FAILURE);
  }

  if (pid != PID_CHILD)
  {
    int wstatus;
    wait(&wstatus);

    if (WIFEXITED(wstatus)) { return WEXITSTATUS(wstatus); }
  }
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

int exec(char* cmd, int argc, char** argv)
{
  int laststatus = execbuiltin(cmd, argc, argv);

  return (laststatus != UNKNOWN) ? laststatus : execextern(cmd, argc, argv);
}


