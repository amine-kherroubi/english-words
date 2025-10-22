# English Words Analysis Program

A C program that analyzes English words and creates various relationships between them, including subwords, verb forms, lexically close words, and anagrams.

## Features

- **Word Analysis**: Count characters, vowels, consonants, and syllables
- **Subword Detection**: Find words contained within larger words
- **Verb Forms**: Generate and link -ing and -ed forms
- **Lexical Proximity**: Identify words that differ by one character
- **Anagram Detection**: Find anagrams of words
- **Alphabetical Ordering**: Check and sort words alphabetically

## Project Structure

```
├── main.c                 # Main program entry point
├── english_words.h        # Core data structures and function declarations
├── ui.h                   # User interface header
├── ui.c                   # User interface implementation
├── word_analysis.c        # Character and word analysis functions
├── word_node.c            # Word node and list operations
├── file_io.c              # File reading operations
├── relationships.c        # Word relationship creation
├── verb_forms.c           # Verb form generation (-ing/-ed)
├── display.c              # Relationship display functions
├── Makefile               # Build configuration
└── README.md              # This file
```

## Building

### Prerequisites
- GCC compiler
- Make utility

### Compilation

```bash
make
```

This will compile all source files and create the `english_words` executable.

### Clean Build

```bash
make clean    # Remove build artifacts
make rebuild  # Clean and rebuild
```

## Usage

1. Run the program:
   ```bash
   ./english_words
   ```

2. Enter the path to your word list file when prompted. The file should contain words separated by whitespace, with syllables separated by slashes (e.g., `hel/lo`).

3. The program will display all loaded words organized by their first letter.

4. Use the menu to explore various word relationships:
   - **0**: Display detailed information about a specific word
   - **1**: Show subword chains
   - **2**: Show verb forms (-ed/-ing)
   - **3**: Show words formed by adding one character (not yet implemented)
   - **4**: Show lexically close words
   - **5**: Show anagrams
   - **6**: Insert a new word
   - **7**: Delete a word
   - **8**: Display statistics
   - **9**: Exit

## Input File Format

The input file should contain one word per line or words separated by whitespace. Syllables within words should be separated by forward slashes:

```
hel/lo
world
pro/gram/ming
an/a/lyze
```

## Code Organization

### Modules

- **word_analysis**: Low-level character and word analysis
- **word_node**: Memory management and linked list operations
- **file_io**: Reading words from files
- **relationships**: Creating links between related words
- **verb_forms**: Generating verb conjugations
- **display**: Printing relationship chains
- **ui**: User interaction and menu handling

### Key Data Structures

- **WordNode**: Represents a word with all its properties and relationships
- **Syllable**: Linked list node for syllable storage
- **LetterList**: Container for words starting with the same letter
- **Statistics**: Holds program statistics

## Platform Support

The program is cross-platform compatible:
- **Windows**: Uses `cls` to clear the screen
- **Unix/Linux/macOS**: Uses `clear` to clear the screen

## Memory Management

The program properly manages dynamic memory:
- All allocated nodes are tracked
- `cleanup_word_lists()` frees all memory before exit
- No memory leaks under normal operation

## Limitations

- Maximum 1000 words per file
- Maximum 50 characters per word
- Maximum 10 characters per syllable
- The "add one character" feature is not yet implemented

## Contributing

When contributing, please:
1. Follow the existing code style
2. Add comments for complex logic
3. Update this README for new features
4. Test on both Windows and Unix-like systems

## License

This project was created as part of an academic assignment at École Nationale Supérieure d'Informatique (ESI).

## Authors

Original implementation: Mohamed El Amine Kherroubi, Ahcen Chabbi
Refactored version: 2025