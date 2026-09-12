#ifndef BUILTIN_H
#define BUILTIN_H

#define HELPTXT \
"msh - Mid Shell is a very simple shell\n\
\n\
  help         prints this help screen\n\
  echo <ARGS>  prints <ARGS> with spaces as separators\n\
  exit         exits the shell\n\
  pwd          prints the current working directory\n\
  cd <DIR>     changes the current working directory to <DIR>\n\
\n\
if a command is entered and it isn't from this list then the shel will\n\
attempt to search for that program in PATH or, if prefixed with './'\n\
will execute a local script/file. if everything fails it will print an\n\
error\n"

#define HELP() ( printf(HELPTXT) )

void exit_cmd(int argc, char** argv);
void cd_cmd(int argc, char** argv);
void pwd_cmd(int argc, char** argv);
void echo_cmd(int argc, char** argv);

#endif
