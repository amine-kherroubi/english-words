# Makefile for English Words Analysis Program

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2 -Iinclude
LDFLAGS = 

# Directories
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
IO_DIR = $(SRC_DIR)/io
UTILS_DIR = $(SRC_DIR)/utils
UI_DIR = $(SRC_DIR)/ui
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIR = include
DATA_DIR = data

# Target
TARGET = $(BIN_DIR)/english_words

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(CORE_DIR)/word_analysis.c \
       $(CORE_DIR)/word_node.c \
       $(CORE_DIR)/relationships.c \
       $(IO_DIR)/file_io.c \
       $(IO_DIR)/display.c \
       $(UTILS_DIR)/verb_forms.c \
       $(UI_DIR)/ui.c

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/word_analysis.o \
       $(OBJ_DIR)/word_node.o \
       $(OBJ_DIR)/relationships.o \
       $(OBJ_DIR)/file_io.o \
       $(OBJ_DIR)/display.o \
       $(OBJ_DIR)/verb_forms.o \
       $(OBJ_DIR)/ui.o

# Default target
.PHONY: all
all: directories $(TARGET)

# Create necessary directories
.PHONY: directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Link executable
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build successful!"

# Compile main
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/english_words.h $(INCLUDE_DIR)/ui.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile core modules
$(OBJ_DIR)/word_analysis.o: $(CORE_DIR)/word_analysis.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/word_node.o: $(CORE_DIR)/word_node.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/relationships.o: $(CORE_DIR)/relationships.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile I/O modules
$(OBJ_DIR)/file_io.o: $(IO_DIR)/file_io.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/display.o: $(IO_DIR)/display.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile utility modules
$(OBJ_DIR)/verb_forms.o: $(UTILS_DIR)/verb_forms.c $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile UI module
$(OBJ_DIR)/ui.o: $(UI_DIR)/ui.c $(INCLUDE_DIR)/ui.h $(INCLUDE_DIR)/english_words.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Run the program
.PHONY: run
run: all
	@cd $(DATA_DIR) && ../$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Full rebuild
.PHONY: rebuild
rebuild: clean all

# Debug build
.PHONY: debug
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Release build
.PHONY: release
release: CFLAGS += -O3 -DNDEBUG
release: clean all

# Check for memory leaks (requires valgrind)
.PHONY: memcheck
memcheck: debug
	@cd $(DATA_DIR) && valgrind --leak-check=full --show-leak-kinds=all ../$(TARGET)

# Static analysis (requires cppcheck)
.PHONY: analyze
analyze:
	@cppcheck --enable=all --std=c99 --suppress=missingIncludeSystem $(SRC_DIR)

# Display help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  run       - Build and run the program"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  debug     - Build with debug symbols"
	@echo "  release   - Build optimized release version"
	@echo "  memcheck  - Run with valgrind memory checker"
	@echo "  analyze   - Run static analysis with cppcheck"
	@echo "  help      - Display this help message"

.PHONY: info
info:
	@echo "Project: English Words Analysis"
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Target: $(TARGET)"
	@echo "Sources: $(SRCS)"