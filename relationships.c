/**
 * Word Relationship Functions
 * Creating links between related words
 */

#include "english_words.h"
#include <stdlib.h>
#include <string.h>

/* Word comparison functions */

bool is_subword(const char *smaller, const char *larger) {
  int smaller_len = strlen(smaller);
  int larger_len = strlen(larger);

  if (smaller_len > larger_len || smaller_len == 0) {
    return false;
  }

  char *temp = (char *)malloc(smaller_len + 2); /* Extra byte for safety */
  if (temp == NULL) {
    return false;
  }

  int j = 0;
  int separations = 0;

  for (int i = 0; i < larger_len && j < smaller_len; i++) {
    if (larger[i] == smaller[j]) {
      temp[j] = larger[i];
      j++;

      if (i < larger_len - 1 && j < smaller_len &&
          larger[i + 1] != smaller[j]) {
        separations++;
      }
    } else {
      if (i < larger_len - 1 && j < smaller_len &&
          larger[i + 1] == smaller[j]) {
        separations++;
      }
    }
  }

  temp[j] = '\0';

  bool result =
      (strcmp(temp, smaller) == 0 &&
       (separations <= 1 || (separations <= 2 && larger[0] == smaller[0])));

  free(temp);
  return result;
}

bool is_one_char_added(const char *smaller, const char *larger) {
  return is_subword(smaller, larger) && strlen(larger) == strlen(smaller) + 1;
}

bool are_lexically_close(const char *word1, const char *word2) {
  int len1 = strlen(word1);
  int len2 = strlen(word2);

  if (len1 != len2) {
    return false;
  }

  int differences = 0;
  for (int i = 0; i < len1; i++) {
    if (word1[i] != word2[i]) {
      differences++;
      if (differences > 1) {
        return false;
      }
    }
  }

  return differences == 1;
}

/* Subword links */

int create_subword_links(void) {
  int link_count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      current->subword_of = NULL;

      for (int j = 0; j < ALPHABET_SIZE; j++) {
        WordNode *candidate = g_word_lists[j].head;

        while (candidate != NULL) {
          if (candidate != current &&
              is_subword(current->clean_word, candidate->clean_word)) {

            if (current->subword_of == NULL ||
                strlen(candidate->clean_word) <
                    strlen(current->subword_of->clean_word)) {
              current->subword_of = candidate;
            }
          }
          candidate = candidate->next;
        }
      }

      if (current->subword_of != NULL) {
        link_count++;
      }

      current = current->next;
    }
  }

  return link_count;
}

/* Verb form links */

int create_verb_form_links(void) {
  int link_count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      current->ing_form = NULL;
      current->ed_form = NULL;

      /* Check for -ing form */
      char *ing = generate_ing_form(current->clean_word);
      if (ing != NULL) {
        /* Search in all lists since the -ing form might start with a different
         * letter */
        for (int k = 0; k < ALPHABET_SIZE; k++) {
          WordNode *ing_node = search_word(g_word_lists[k].head, ing);
          if (ing_node != NULL && ing_node != current) {
            current->ing_form = ing_node;
            link_count++;
            break;
          }
        }
        free(ing);
      }

      /* Check for -ed form */
      char *ed = generate_ed_form(current->clean_word);
      if (ed != NULL) {
        /* Search in all lists since the -ed form might start with a different
         * letter */
        for (int k = 0; k < ALPHABET_SIZE; k++) {
          WordNode *ed_node = search_word(g_word_lists[k].head, ed);
          if (ed_node != NULL && ed_node != current) {
            current->ed_form = ed_node;
            link_count++;
            break;
          }
        }
        free(ed);
      }

      current = current->next;
    }
  }

  return link_count;
}

/* Lexically close links */

int create_lexically_close_links(void) {
  int link_count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      current->lexically_close = NULL;
      bool found_self = false;

      for (int j = 0; j < ALPHABET_SIZE; j++) {
        WordNode *candidate = g_word_lists[j].head;

        while (candidate != NULL) {
          if (candidate == current) {
            found_self = true;
          } else if (found_self && are_lexically_close(current->clean_word,
                                                       candidate->clean_word)) {
            current->lexically_close = candidate;
            link_count++;
            break;
          }
          candidate = candidate->next;
        }

        if (current->lexically_close != NULL) {
          break;
        }
      }

      current = current->next;
    }
  }

  return link_count;
}

/* Anagram links */

int create_anagram_links(void) {
  int link_count = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      current->anagram = NULL;
      bool found_self = false;

      for (int j = 0; j < ALPHABET_SIZE; j++) {
        WordNode *candidate = g_word_lists[j].head;

        while (candidate != NULL) {
          if (candidate == current) {
            found_self = true;
          } else if (found_self &&
                     strcmp(current->clean_word, candidate->clean_word) != 0 &&
                     strcmp(current->alphabetically_sorted,
                            candidate->alphabetically_sorted) == 0) {
            current->anagram = candidate;
            link_count++;
            break;
          }
          candidate = candidate->next;
        }

        if (current->anagram != NULL) {
          break;
        }
      }

      current = current->next;
    }
  }

  return link_count;
}