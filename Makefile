OBJECTS := $(addprefix build/, main.o shell.o)
CFLAGS  := -Iinclude
VPATH   := src include
bin     := bin/msh.out

$(bin): $(OBJECTS)
	$(CC) -o $@ $^

build/main.o: main.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

build/shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

.DELETE_ON_ERROR:
.PHONY: clean debug
clean:
	-$(RM) $(OBJECTS) $(bin)

debug: CFLAGS += -g -Werror
debug: $(bin)

