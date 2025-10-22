/**
 * English Words Analysis Library
 * Data structures and functions for analyzing English words
 *
 * Improvements:
 * - Better const correctness
 * - Enhanced error code enumeration
 * - Improved documentation
 */

#ifndef ENGLISH_WORDS_H
#define ENGLISH_WORDS_H

#include <stdbool.h>

/* Constants */
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50
#define MAX_SYLLABLE_LENGTH 10
#define ALPHABET_SIZE 26
#define MAX_FILENAME_LENGTH 100
#define INVALID_LIST_INDEX 26

/* Error codes */
typedef enum {
  SUCCESS = 0,
  ERROR_FILE_NOT_FOUND = -1,
  ERROR_MEMORY_ALLOCATION = -2,
  ERROR_INVALID_INPUT = -3,
  ERROR_WORD_EXISTS = -4,
  ERROR_WORD_NOT_FOUND = -5
} ErrorCode;

/* Forward declarations */
typedef struct Syllable Syllable;
typedef struct WordNode WordNode;
typedef struct LetterList LetterList;

/* Syllable structure for syllable lists */
struct Syllable {
  char text[MAX_SYLLABLE_LENGTH];
  Syllable *next;
};

/* Word node structure containing word data and relationships */
struct WordNode {
  char *original_word;            /* Word as read from file (with slashes) */
  char *clean_word;               /* Word without slashes */
  int char_count;                 /* Number of characters */
  int consonant_count;            /* Number of consonants */
  int vowel_count;                /* Number of vowels */
  int syllable_count;             /* Number of syllables */
  Syllable *syllables;            /* List of syllables */
  bool is_alphabetically_ordered; /* Characters in alphabetical order */
  char *alphabetically_sorted;    /* Word with sorted characters */

  WordNode *next; /* Next word in list */
  WordNode *prev; /* Previous word in list */

  /* Word relationships */
  WordNode *subword_of;      /* Larger word containing this word */
  WordNode *ed_form;         /* Past participle form */
  WordNode *ing_form;        /* Gerund form */
  WordNode *add_one_char;    /* Word with one additional character */
  WordNode *lexically_close; /* Lexically similar word */
  WordNode *anagram;         /* Anagram of this word */
};

/* Letter list structure (one per alphabet letter) */
struct LetterList {
  WordNode *head;
};

/* Global word lists array (A-Z plus one for invalid words) */
extern LetterList g_word_lists[ALPHABET_SIZE + 1];

/* Statistics structure */
typedef struct {
  int word_count;
  int subword_links;
  int verb_form_links;
  int lexclose_links;
  int anagram_links;
} Statistics;

/* Memory management */
WordNode *allocate_word_node(void);
Syllable *allocate_syllable(void);
void free_word_node(WordNode *node);
void free_syllable(Syllable *syll);
void cleanup_word_lists(void);

/* Character operations */
bool is_vowel(char c);
bool is_consonant(char c);
int get_ascii_code(char c);

/* Word analysis */
int count_vowels(const char *word);
int count_consonants(const char *word);
int count_characters(const char *word);
int count_syllables(const char *word);
bool is_word_alphabetically_ordered(const char *word);
char *sort_word_alphabetically(const char *word);
char *remove_slashes(const char *word);
int get_word_letter_index(const char *word);
bool is_valid_word_format(const char *word);

/* Syllable operations */
Syllable *parse_syllables(const char *word);
void print_syllable_list(const Syllable *syllables);

/* Word node operations */
void initialize_word_node(WordNode *node);
void print_word_details(const WordNode *node);

/* List operations */
ErrorCode insert_word_sorted_by_length(WordNode **head, const char *word);
bool delete_word_from_list(WordNode **head, const char *word);
WordNode *search_word(const WordNode *head, const char *word);
void print_word_list(const WordNode *head);
void print_all_word_lists(void);
void remove_duplicate_words(void);

/* File operations */
int load_words_from_file(const char *filename);
bool save_word_to_file(const char *word);
bool save_all_words_to_file(void);

/* Relationship creation */
int create_subword_links(void);
int create_verb_form_links(void);
int create_lexically_close_links(void);
int create_anagram_links(void);

/* Relationship display */
void print_subword_chains(void);
void print_verb_forms(void);
void print_lexically_close_words(void);
void print_anagrams(void);

/* Verb form generation */
char *generate_ing_form(const char *verb);
char *generate_ed_form(const char *verb);

/* Word comparison */
bool is_subword(const char *smaller, const char *larger);
bool is_one_char_added(const char *smaller, const char *larger);
bool are_lexically_close(const char *word1, const char *word2);

#endif /* ENGLISH_WORDS_H */