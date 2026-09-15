# DESCRIPTION

**Mid Shell** is a simple shell built in C

# INSTALLATION

Download and extract the tarball

```
curl -Lo msh-0.0.1-alpha.tar.gz https://github.com/ajellofello/msh/archive/refs/tags/v0.0.1-alpha.tar.gz
tar -zxf msh-0.0.1-alpha.tar.gz
```

Or clone the repo

```
git clone https://github.com/ajellofello/msh.git && cd msh
```

then run `make`

```
make
```

The executable `msh` will be in `bin/`. Run `help` to get an overview on
the shell

**NOTE:** This shell is not intended as anything more than a practice project
for myself. So please don't go and replace your shell with fucking _mid shell_

# FEATURES

**CURRENT FEATURES**

- execute [builtin](#BUILTINS) commands
- execute any external command in `$PATH`
- run local files

_Yeah there isn't much there :p_

**FUTURE FEATURES**

- Using GNU readline
- Output redirection
- Piping
- Handling quotes in prompt
- Ignore `SIGINT` (correctly)

# BUILTINS

- `help`        prints this help screen
- `echo <ARGS>` prints `<ARGS>` with spaces as separators
- `exit <STAT>` exits the shell with exit code `<STAT>`
- `pwd`         the current working directory
- `cd <DIR>`    changes the current working directory to `<DIR>`

_Again there isn't much there_
