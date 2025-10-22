# English Words Analysis Program

A C program that analyzes English words and discovers linguistic relationships including subwords, verb conjugations, lexical proximity, and anagrams.

## Recent Improvements (2025 Refactored Version)

### Memory & Safety
- **Better error handling** - Added ErrorCode enumeration for clearer error tracking
- **Fixed memory leaks** - Proper cleanup in verb form generation functions
- **Improved buffer safety** - Better bounds checking throughout
- **Enhanced null checking** - All functions now validate input pointers

### Algorithm Improvements
- **Circular chain detection** - Prevents infinite loops in relationship chains
- **Robust word validation** - Added `is_valid_word_format()` function
- **Better file I/O** - More robust file reading with validation
- **Safer string operations** - Using `strncpy` and proper null termination

### Code Quality
- **Const correctness** - Better use of const qualifiers
- **Cleaner casting** - Proper use of unsigned char casts for ctype functions
- **Better documentation** - Improved comments and function headers
- **Error messages** - More informative error reporting with perror()

### Performance
- **Optimized comparisons** - More efficient string comparison algorithms
- **Better memory allocation** - Accurate buffer size calculations
- **Input validation** - Early rejection of invalid input

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
make run
```

Or directly:
```bash
./build/bin/english_words
```

### Clean
```bash
make clean      # Remove build artifacts
make rebuild    # Clean and rebuild
```

## Usage

The program loads words from `persistence/words.txt` on startup and displays them organized by first letter. Use the interactive menu to explore relationships:

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

Words in `persistence/words.txt` should have syllables separated by forward slashes:

```
hel/lo
world
pro/gram/ming
ed/u/ca/tion
```

## Project Structure

```
.
├── include/
│   ├── english_words.h     # Core data structures and API
│   └── ui.h               # User interface declarations
├── src/
│   ├── main.c             # Program entry point
│   ├── core/
│   │   ├── word_analysis.c    # Character and word analysis
│   │   ├── word_node.c        # Memory management and list operations
│   │   └── relationships.c    # Relationship creation algorithms
│   ├── io/
│   │   ├── file_io.c          # File I/O operations
│   │   └── display.c          # Relationship display
│   ├── utils/
│   │   └── verb_forms.c       # Verb conjugation rules
│   └── ui/
│       └── ui.c               # User interface implementation
├── persistence/
│   └── words.txt          # Word database
├── build/                 # Build artifacts (generated)
│   ├── obj/              # Object files
│   └── bin/              # Executable
├── Makefile              # Build configuration
├── .gitignore            # Git ignore rules
└── README.md             # This file
```

## Technical Details

### Data Structures
- **WordNode** - Doubly-linked list node containing word properties and relationship pointers
- **Syllable** - Linked list for syllable storage
- **LetterList** - 26 lists (A-Z) for efficient word organization

### Algorithms
- **Subword Detection** - Pattern matching with separation tracking
- **Verb Generation** - Rule-based conjugation (CVC doubling, silent-e handling, etc.)
- **Lexical Distance** - Single-character difference detection with circular chain prevention
- **Anagram Detection** - Sorted character comparison

### Constraints
- Maximum 1000 words
- Maximum 50 characters per word
- Maximum 10 characters per syllable

### Error Codes
- `SUCCESS = 0` - Operation completed successfully
- `ERROR_FILE_NOT_FOUND = -1` - File not found
- `ERROR_MEMORY_ALLOCATION = -2` - Memory allocation failed
- `ERROR_INVALID_INPUT = -3` - Invalid input provided
- `ERROR_WORD_EXISTS = -4` - Word already exists
- `ERROR_WORD_NOT_FOUND = -5` - Word not found

## Requirements

- **Compiler** - GCC with C99 support
- **Build System** - GNU Make
- **Platform** - Cross-platform (Windows/Linux/macOS)

## Memory Management

All dynamic memory is properly tracked and freed. Use valgrind to verify:
```bash
make memcheck
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

## Contributing

This is an academic project from École Nationale Supérieure d'Informatique (ESI).

**Original Authors:** Mohamed El Amine Kherroubi, Ahcen Chabbi  
**Refactored:** 2025

## Changelog

### Version 2.0 (2025 Refactor)
- Fixed Makefile to run from project root
- Renamed data → persistence directory
- Added comprehensive error handling
- Fixed memory leaks in verb generation
- Improved circular chain detection
- Enhanced input validation
- Better const correctness
- More informative error messages
- Safer string operations
- Optimized algorithms

### Version 1.0 (Original)
- Initial implementation
- Basic word analysis features
- Relationship detection
- File I/O operations