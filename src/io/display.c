/**
 * Display Functions for Word Relationships
 * Printing chains and relationships
 *
 * Improvements:
 * - Better circular chain detection
 * - Prevents infinite loops
 * - More robust chain traversal
 */

#include "../../include/english_words.h"
#include <stdio.h>

#define MAX_CHAIN_LENGTH 100

void print_subword_chains(void) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      if (current->subword_of != NULL) {
        printf("%s --> ", current->clean_word);
        printf("%s", current->subword_of->clean_word);

        /* Follow the chain with loop detection */
        WordNode *chain = current->subword_of->subword_of;
        WordNode *visited[MAX_CHAIN_LENGTH];
        int visited_count = 0;

        visited[visited_count++] = current;
        visited[visited_count++] = current->subword_of;

        while (chain != NULL && visited_count < MAX_CHAIN_LENGTH) {
          /* Check if we've seen this node before */
          bool is_loop = false;
          for (int j = 0; j < visited_count; j++) {
            if (visited[j] == chain) {
              is_loop = true;
              break;
            }
          }

          if (is_loop) {
            printf(" --> (loop detected)");
            break;
          }

          printf(" --> %s", chain->clean_word);
          visited[visited_count++] = chain;
          chain = chain->subword_of;
        }

        printf(" --> (end)\n");
      }
      current = current->next;
    }
  }
}

void print_verb_forms(void) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      if (current->ed_form != NULL || current->ing_form != NULL) {
        printf("%s --> ", current->clean_word);

        if (current->ed_form != NULL) {
          printf("%s", current->ed_form->clean_word);
        } else {
          printf("(no -ed form)");
        }

        printf(" --> ");

        if (current->ing_form != NULL) {
          printf("%s\n", current->ing_form->clean_word);
        } else {
          printf("(no -ing form)\n");
        }
      }
      current = current->next;
    }
  }
}

void print_lexically_close_words(void) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      if (current->lexically_close != NULL) {
        printf("%s --> ", current->clean_word);

        WordNode *chain = current->lexically_close;
        WordNode *visited[MAX_CHAIN_LENGTH];
        int visited_count = 0;

        visited[visited_count++] = current;

        while (chain != NULL && visited_count < MAX_CHAIN_LENGTH) {
          /* Check if we've seen this node before (circular detection) */
          bool is_loop = false;
          for (int j = 0; j < visited_count; j++) {
            if (visited[j] == chain) {
              is_loop = true;
              break;
            }
          }

          if (is_loop) {
            break;
          }

          printf("%s --> ", chain->clean_word);
          visited[visited_count++] = chain;
          chain = chain->lexically_close;
        }

        printf("(end)\n");
      }
      current = current->next;
    }
  }
}

void print_anagrams(void) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      if (current->anagram != NULL) {
        printf("%s --> ", current->clean_word);

        WordNode *chain = current->anagram;
        WordNode *visited[MAX_CHAIN_LENGTH];
        int visited_count = 0;

        visited[visited_count++] = current;

        while (chain != NULL && visited_count < MAX_CHAIN_LENGTH) {
          /* Check if we've seen this node before (circular detection) */
          bool is_loop = false;
          for (int j = 0; j < visited_count; j++) {
            if (visited[j] == chain) {
              is_loop = true;
              break;
            }
          }

          if (is_loop) {
            break;
          }

          printf("%s --> ", chain->clean_word);
          visited[visited_count++] = chain;
          chain = chain->anagram;
        }

        printf("(end)\n");
      }
      current = current->next;
    }
  }
}