/**
 * Display Functions for Word Relationships
 * Printing chains and relationships
 */

#include "english_words.h"
#include <stdio.h>

void print_subword_chains(void) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      if (current->subword_of != NULL) {
        printf("%s --> ", current->clean_word);
        printf("%s", current->subword_of->clean_word);

        /* Follow the chain */
        WordNode *chain = current->subword_of->subword_of;
        while (chain != NULL) {
          printf(" --> %s", chain->clean_word);
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
        while (chain != NULL &&
               chain->lexically_close != current->lexically_close) {
          printf("%s --> ", chain->clean_word);
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
        while (chain != NULL && chain->anagram != current->anagram) {
          printf("%s --> ", chain->clean_word);
          chain = chain->anagram;
        }

        printf("(end)\n");
      }
      current = current->next;
    }
  }
}