/**
 * File Input/Output Operations
 * Reading words from files
 */

#include "english_words.h"
#include <stdio.h>
#include <string.h>

/* Global word lists definition */
LetterList g_word_lists[ALPHABET_SIZE + 1];

static int read_words_to_array(const char *filename,
                               char words[][MAX_WORD_LENGTH]) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return -1;
  }

  int count = 0;
  while (count < MAX_WORDS && !feof(file)) {
    if (fscanf(file, "%49s", words[count]) == 1) {
      count++;
    }
  }

  fclose(file);
  return count;
}

static void insert_words_into_lists(char words[][MAX_WORD_LENGTH], int count) {
  /* Initialize all lists to NULL */
  for (int i = 0; i <= ALPHABET_SIZE; i++) {
    g_word_lists[i].head = NULL;
  }

  /* Insert each word into appropriate list */
  for (int i = 0; i < count; i++) {
    int index = get_word_letter_index(words[i]);
    insert_word_sorted_by_length(&g_word_lists[index].head, words[i]);
  }
}

int load_words_from_file(const char *filename) {
  char words[MAX_WORDS][MAX_WORD_LENGTH];

  int word_count = read_words_to_array(filename, words);
  if (word_count == -1) {
    return -1;
  }

  insert_words_into_lists(words, word_count);

  return word_count;
}