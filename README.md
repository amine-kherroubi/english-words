# English Words Analysis Program

A C program that analyzes English words and discovers linguistic relationships including subwords, verb conjugations, lexical proximity, and anagrams.

## Features

- **Word Analysis** - Count characters, vowels, consonants, and syllables
- **Subword Detection** - Find words contained within larger words (e.g., "art" in "start")
- **Verb Forms** - Link base verbs with their -ed and -ing forms
- **Lexical Proximity** - Find words differing by exactly one character
- **Anagram Detection** - Discover anagrams (e.g., "listen" and "silent")
- **Dynamic Management** - Insert and delete words with automatic relationship recalculation

## Quick Start

### Build
```bash
make
```

### Run
```bash
./english_words
```

### Clean
```bash
make clean      # Remove build artifacts
make rebuild    # Clean and rebuild
```

## Usage

The program loads words from `words.txt` on startup and displays them organized by first letter. Use the interactive menu to explore relationships:

| Option | Action                                                  |
| ------ | ------------------------------------------------------- |
| **0**  | Display detailed information about a word               |
| **1**  | Show subword chains                                     |
| **2**  | Show verb forms (-ed/-ing)                              |
| **3**  | Show words with one character added *(not implemented)* |
| **4**  | Show lexically close words                              |
| **5**  | Show anagrams                                           |
| **6**  | Insert a new word                                       |
| **7**  | Delete a word                                           |
| **8**  | Display statistics                                      |
| **9**  | Exit                                                    |

## Word File Format

Words in `words.txt` should have syllables separated by forward slashes:

```
hel/lo
world
pro/gram/ming
ed/u/ca/tion
```

## Project Structure

```
├── main.c              # Program entry point
├── english_words.h     # Core data structures and API
├── ui.h/ui.c          # User interface
├── word_analysis.c     # Character and word analysis
├── word_node.c         # Memory management and list operations
├── file_io.c          # File I/O operations
├── relationships.c     # Relationship creation algorithms
├── verb_forms.c       # Verb conjugation rules
├── display.c          # Relationship display
├── Makefile           # Build configuration
└── words.txt          # Word database
```

## Technical Details

### Data Structures
- **WordNode** - Doubly-linked list node containing word properties and relationship pointers
- **Syllable** - Linked list for syllable storage
- **LetterList** - 26 lists (A-Z) for efficient word organization

### Algorithms
- **Subword Detection** - Pattern matching with separation tracking
- **Verb Generation** - Rule-based conjugation (CVC doubling, silent-e handling, etc.)
- **Lexical Distance** - Single-character difference detection
- **Anagram Detection** - Sorted character comparison

### Constraints
- Maximum 1000 words
- Maximum 50 characters per word
- Maximum 10 characters per syllable

## Requirements

- **Compiler** - GCC with C99 support
- **Build System** - GNU Make
- **Platform** - Cross-platform (Windows/Linux/macOS)

## Memory Management

All dynamic memory is properly tracked and freed. Use valgrind to verify:
```bash
valgrind --leak-check=full ./english_words
```

## Examples

### Subword Chain
```
art --> start --> restart --> (end)
```

### Verb Forms
```
study --> studied --> studying
```

### Lexically Close
```
cat --> bat --> hat --> mat --> (end)
```

### Anagrams
```
listen --> silent --> enlist --> (end)
```

## Project Information

This academic project originates from École Nationale Supérieure d'Informatique (ESI).

**Original Authors (2023):** Mohamed El Amine Kherroubi, Ahcen Chabbi  
**Refactored by AI (2025)**