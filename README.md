# DESCRIPTION

**Mid Shell** is a simple shell built in C

# INSTALLATION

Clone the repo or install the tar ball, create `build/` and `bin/` & run `make`
in the root of the project

```
git clone https://github.com/ajellofello/msh.git && cd msh
mkdir build bin
make
```

The executable `msh` will be in `bin/`.

**NOTE:** This shell is not intended as anything more than a practice project
for myself. So please don't go and replace your shell with fucking _mid shell_

# FUTURE FEATURES

This shell is currently very incomplete. There are a lot of features I would like
to add, like:

- Using GNU readline
- Output redirection
- Piping
- Handling quotes in prompt
- Ignore `SIGINT` (correctly)

