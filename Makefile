# Makefile for English Words Analysis Program

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2
TARGET = english_words
OBJS = main.o word_analysis.o word_node.o file_io.o relationships.o verb_forms.o display.o ui.o

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main
main.o: main.c english_words.h ui.h
	$(CC) $(CFLAGS) -c main.c

# Compile word analysis module
word_analysis.o: word_analysis.c english_words.h
	$(CC) $(CFLAGS) -c word_analysis.c

# Compile word node module
word_node.o: word_node.c english_words.h
	$(CC) $(CFLAGS) -c word_node.c

# Compile file I/O module
file_io.o: file_io.c english_words.h
	$(CC) $(CFLAGS) -c file_io.c

# Compile relationships module
relationships.o: relationships.c english_words.h
	$(CC) $(CFLAGS) -c relationships.c

# Compile verb forms module
verb_forms.o: verb_forms.c english_words.h
	$(CC) $(CFLAGS) -c verb_forms.c

# Compile display module
display.o: display.c english_words.h
	$(CC) $(CFLAGS) -c display.c

# Compile UI module
ui.o: ui.c ui.h english_words.h
	$(CC) $(CFLAGS) -c ui.c

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild