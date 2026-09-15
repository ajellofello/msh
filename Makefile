OBJS    := $(addprefix build/, main.o alloc.o shell.o builtin.o)
TARGET  := bin/msh
CFLAGS  := -Iinclude -std=c99
VPATH   := src include
RM      := rm -rf

$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) -o $@ $^

build/main.o: main.c shell.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/shell.o: shell.c shell.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/builtin.o: builtin.c builtin.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/alloc.o: alloc.c alloc.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

.PHONY: clean debug
clean:
	-$(RM) $(OBJS) $(TARGET) bin build

debug: CFLAGS += -g -Werror -Wextra
debug: $(TARGET)

