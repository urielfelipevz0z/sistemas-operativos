CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g -O0
INCLUDES = -Iinclude
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/sistemas_operativos

SOURCES = principal.c $(SRC_DIR)/alu.c $(SRC_DIR)/interprete.c $(SRC_DIR)/imprimir.c
OBJECTS = $(BUILD_DIR)/principal.o $(BUILD_DIR)/alu.o $(BUILD_DIR)/interprete.o $(BUILD_DIR)/imprimir.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@
	@echo "Build complete: $(TARGET)"

$(BUILD_DIR)/principal.o: principal.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/alu.o: $(SRC_DIR)/alu.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/interprete.o: $(SRC_DIR)/interprete.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/imprimir.o: $(SRC_DIR)/imprimir.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

run: $(TARGET)
	$(TARGET)

$(BUILD_DIR)/principal.o: $(INCLUDE_DIR)/alu.h $(INCLUDE_DIR)/interprete.h $(INCLUDE_DIR)/imprimir.h
$(BUILD_DIR)/alu.o: $(INCLUDE_DIR)/alu.h
$(BUILD_DIR)/interprete.o: $(INCLUDE_DIR)/interprete.h $(INCLUDE_DIR)/alu.h $(INCLUDE_DIR)/imprimir.h
$(BUILD_DIR)/imprimir.o: $(INCLUDE_DIR)/imprimir.h $(INCLUDE_DIR)/alu.h