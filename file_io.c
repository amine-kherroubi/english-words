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
  char buffer[512]; /* Buffer for reading lines */

  while (count < MAX_WORDS && fgets(buffer, sizeof(buffer), file) != NULL) {
    /* Parse multiple words from the line */
    char *token = strtok(buffer, " \t\n\r");

    while (token != NULL && count < MAX_WORDS) {
      size_t len = strlen(token);

      /* Check if word fits in our array */
      if (len > 0 && len < MAX_WORD_LENGTH) {
        strncpy(words[count], token, MAX_WORD_LENGTH - 1);
        words[count][MAX_WORD_LENGTH - 1] = '\0';
        count++;
      } else if (len >= MAX_WORD_LENGTH) {
        fprintf(stderr, "Warning: Word too long, skipping: %.20s...\n", token);
      }

      token = strtok(NULL, " \t\n\r");
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