CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g -O0 -Iinclude
TARGET = bin/sistemas_operativos

SOURCES = principal.c src/alu.c src/interprete.c src/imprimir.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(addprefix build/, $(notdir $(OBJECTS)))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $^ -o $@
	@echo "Build complete: $@"

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin
	@echo "Clean complete"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run