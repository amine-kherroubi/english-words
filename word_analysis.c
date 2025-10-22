/**
 * Word Analysis Functions
 * Character and word-level analysis operations
 */

#include "english_words.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Character operations */

bool is_vowel(char c) {
  char vowels[] = "aeiouyAEIOUY";
  for (int i = 0; vowels[i] != '\0'; i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

bool is_consonant(char c) { return isalpha(c) && !is_vowel(c); }

int get_ascii_code(char c) { return (int)c; }

/* Word counting operations */

int count_vowels(const char *word) {
  int count = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (is_vowel(word[i])) {
      count++;
    }
  }
  return count;
}

int count_consonants(const char *word) {
  int count = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (is_consonant(word[i])) {
      count++;
    }
  }
  return count;
}

int count_characters(const char *word) {
  return count_vowels(word) + count_consonants(word);
}

int count_syllables(const char *word) {
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
  int len = strlen(word);
  char *result = (char *)malloc(len + 1);
  if (result == NULL) {
    return NULL;
  }

  int j = 0;
  for (int i = 0; i < len; i++) {
    if (word[i] != '/') {
      result[j++] = word[i];
    }
  }
  result[j] = '\0';

  return result;
}

bool is_word_alphabetically_ordered(const char *word) {
  int len = strlen(word);
  for (int i = 0; i < len - 1; i++) {
    if (tolower(word[i]) > tolower(word[i + 1])) {
      return false;
    }
  }
  return true;
}

char *sort_word_alphabetically(const char *word) {
  int len = strlen(word);
  char *sorted = (char *)malloc(len + 1);
  if (sorted == NULL) {
    return NULL;
  }

  strcpy(sorted, word);

  /* Simple bubble sort */
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      if (tolower(sorted[i]) > tolower(sorted[j])) {
        char temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
  }

  return sorted;
}

int get_word_letter_index(const char *word) {
  /* Check if word contains only alphabetic characters and slashes */
  for (int i = 0; word[i] != '\0'; i++) {
    if (!isalpha(word[i]) && word[i] != '/') {
      return ALPHABET_SIZE; /* Invalid word index */
    }
  }

  /* Return index based on first letter (0-25 for A-Z) */
  return toupper(word[0]) - 'A';
}

/* Syllable operations */

Syllable *parse_syllables(const char *word) {
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
          return head;
        }

        strcpy(new_syll->text, buffer);
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
      return head;
    }

    strcpy(new_syll->text, buffer);
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