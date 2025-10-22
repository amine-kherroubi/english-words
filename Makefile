# Makefile for English Words Analysis Program

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2
TARGET = english_words
BUILD_DIR = build
SRC_FILES = main.c word_analysis.c word_node.c file_io.c relationships.c verb_forms.c display.c ui.c
OBJS = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link all object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main
$(BUILD_DIR)/main.o: main.c english_words.h ui.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

# Compile word analysis module
$(BUILD_DIR)/word_analysis.o: word_analysis.c english_words.h
	$(CC) $(CFLAGS) -c word_analysis.c -o $(BUILD_DIR)/word_analysis.o

# Compile word node module
$(BUILD_DIR)/word_node.o: word_node.c english_words.h
	$(CC) $(CFLAGS) -c word_node.c -o $(BUILD_DIR)/word_node.o

# Compile file I/O module
$(BUILD_DIR)/file_io.o: file_io.c english_words.h
	$(CC) $(CFLAGS) -c file_io.c -o $(BUILD_DIR)/file_io.o

# Compile relationships module
$(BUILD_DIR)/relationships.o: relationships.c english_words.h
	$(CC) $(CFLAGS) -c relationships.c -o $(BUILD_DIR)/relationships.o

# Compile verb forms module
$(BUILD_DIR)/verb_forms.o: verb_forms.c english_words.h
	$(CC) $(CFLAGS) -c verb_forms.c -o $(BUILD_DIR)/verb_forms.o

# Compile display module
$(BUILD_DIR)/display.o: display.c english_words.h
	$(CC) $(CFLAGS) -c display.c -o $(BUILD_DIR)/display.o

# Compile UI module
$(BUILD_DIR)/ui.o: ui.c ui.h english_words.h
	$(CC) $(CFLAGS) -c ui.c -o $(BUILD_DIR)/ui.o

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild