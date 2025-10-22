/**
 * Word Analysis Functions
 * Character and word-level analysis operations
 *
 * Improvements:
 * - Added word format validation
 * - Better bounds checking
 * - Improved const correctness
 */

#include "../../include/english_words.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Character operations */

bool is_vowel(char c) {
  c = tolower((unsigned char)c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

bool is_consonant(char c) { return isalpha((unsigned char)c) && !is_vowel(c); }

int get_ascii_code(char c) { return (int)(unsigned char)c; }

/* Word counting operations */

int count_vowels(const char *word) {
  if (word == NULL)
    return 0;

  int count = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (is_vowel(word[i])) {
      count++;
    }
  }
  return count;
}

int count_consonants(const char *word) {
  if (word == NULL)
    return 0;

  int count = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (is_consonant(word[i])) {
      count++;
    }
  }
  return count;
}

int count_characters(const char *word) {
  if (word == NULL)
    return 0;
  return count_vowels(word) + count_consonants(word);
}

int count_syllables(const char *word) {
  if (word == NULL)
    return 0;

  int count = 1;
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == '/') {
      count++;
    }
  }
  return count;
}

/* Word transformation operations */

char *remove_slashes(const char *word) {
  if (word == NULL)
    return NULL;

  size_t len = strlen(word);
  char *result = (char *)malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if (word[i] != '/') {
      result[j++] = word[i];
    }
  }
  result[j] = '\0';

  return result;
}

bool is_word_alphabetically_ordered(const char *word) {
  if (word == NULL || word[0] == '\0')
    return true;

  size_t len = strlen(word);
  for (size_t i = 0; i < len - 1; i++) {
    if (tolower((unsigned char)word[i]) > tolower((unsigned char)word[i + 1])) {
      return false;
    }
  }
  return true;
}

char *sort_word_alphabetically(const char *word) {
  if (word == NULL)
    return NULL;

  size_t len = strlen(word);
  char *sorted = (char *)malloc(len + 1);
  if (sorted == NULL) {
    return NULL;
  }

  strcpy(sorted, word);

  /* Simple bubble sort */
  for (size_t i = 0; i < len - 1; i++) {
    for (size_t j = i + 1; j < len; j++) {
      if (tolower((unsigned char)sorted[i]) >
          tolower((unsigned char)sorted[j])) {
        char temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
  }

  return sorted;
}

bool is_valid_word_format(const char *word) {
  if (word == NULL || word[0] == '\0')
    return false;

  /* Check length */
  size_t len = strlen(word);
  if (len >= MAX_WORD_LENGTH)
    return false;

  /* Check for valid characters (letters and slashes only) */
  for (size_t i = 0; i < len; i++) {
    if (!isalpha((unsigned char)word[i]) && word[i] != '/') {
      return false;
    }
  }

  /* Check for consecutive slashes */
  for (size_t i = 0; i < len - 1; i++) {
    if (word[i] == '/' && word[i + 1] == '/') {
      return false;
    }
  }

  /* Check for leading/trailing slashes */
  if (word[0] == '/' || word[len - 1] == '/') {
    return false;
  }

  return true;
}

int get_word_letter_index(const char *word) {
  if (word == NULL || word[0] == '\0') {
    return INVALID_LIST_INDEX;
  }

  /* Check if word contains only alphabetic characters and slashes */
  for (int i = 0; word[i] != '\0'; i++) {
    if (!isalpha((unsigned char)word[i]) && word[i] != '/') {
      return INVALID_LIST_INDEX;
    }
  }

  /* Return index based on first letter (0-25 for A-Z) */
  return toupper((unsigned char)word[0]) - 'A';
}

/* Syllable operations */

Syllable *parse_syllables(const char *word) {
  if (word == NULL)
    return NULL;

  Syllable *head = NULL;
  Syllable *tail = NULL;
  char buffer[MAX_SYLLABLE_LENGTH];
  int buffer_index = 0;

  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == '/') {
      if (buffer_index > 0) {
        buffer[buffer_index] = '\0';

        Syllable *new_syll = allocate_syllable();
        if (new_syll == NULL) {
          /* Free what we've allocated so far */
          while (head != NULL) {
            Syllable *temp = head->next;
            free_syllable(head);
            head = temp;
          }
          return NULL;
        }

        strncpy(new_syll->text, buffer, MAX_SYLLABLE_LENGTH - 1);
        new_syll->text[MAX_SYLLABLE_LENGTH - 1] = '\0';
        new_syll->next = NULL;

        if (head == NULL) {
          head = new_syll;
          tail = new_syll;
        } else {
          tail->next = new_syll;
          tail = new_syll;
        }

        buffer_index = 0;
      }
    } else {
      if (buffer_index < MAX_SYLLABLE_LENGTH - 1) {
        buffer[buffer_index++] = word[i];
      }
    }
  }

  /* Add the last syllable */
  if (buffer_index > 0) {
    buffer[buffer_index] = '\0';

    Syllable *new_syll = allocate_syllable();
    if (new_syll == NULL) {
      /* Free what we've allocated so far */
      while (head != NULL) {
        Syllable *temp = head->next;
        free_syllable(head);
        head = temp;
      }
      return NULL;
    }

    strncpy(new_syll->text, buffer, MAX_SYLLABLE_LENGTH - 1);
    new_syll->text[MAX_SYLLABLE_LENGTH - 1] = '\0';
    new_syll->next = NULL;

    if (head == NULL) {
      head = new_syll;
    } else {
      tail->next = new_syll;
    }
  }

  return head;
}

void print_syllable_list(const Syllable *syllables) {
  const Syllable *current = syllables;
  while (current != NULL) {
    printf("%s", current->text);
    if (current->next != NULL) {
      printf(" / ");
    }
    current = current->next;
  }
}