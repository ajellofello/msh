OBJECTS := $(addprefix build/, main.o shell.o builtin.o)
CFLAGS  := -Iinclude
VPATH   := src include
bin     := bin/msh.out

$(bin): $(OBJECTS)
	$(CC) -o $@ $^

build/main.o: main.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

build/shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

build/builtin.o: builtin.c builtin.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean debug
clean:
	-$(RM) $(OBJECTS) $(bin)

debug: CFLAGS += -g -Werror
debug: $(bin)

