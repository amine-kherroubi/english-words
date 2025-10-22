/**
 * Word Node Operations
 * Memory management and node manipulation
 */

#include "english_words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Memory management */

WordNode *allocate_word_node(void) {
  WordNode *node = (WordNode *)malloc(sizeof(WordNode));
  if (node == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for word node.\n");
    return NULL;
  }

  /* Initialize all fields to NULL/0 */
  memset(node, 0, sizeof(WordNode));

  return node;
}

Syllable *allocate_syllable(void) {
  Syllable *syll = (Syllable *)malloc(sizeof(Syllable));
  if (syll == NULL) {
    fprintf(stderr, "Error: Unable to allocate memory for syllable.\n");
    return NULL;
  }

  memset(syll, 0, sizeof(Syllable));

  return syll;
}

void free_word_node(WordNode *node) {
  if (node == NULL) {
    return;
  }

  free(node->original_word);
  free(node->clean_word);
  free(node->alphabetically_sorted);

  /* Free syllable list */
  Syllable *current = node->syllables;
  while (current != NULL) {
    Syllable *next = current->next;
    free_syllable(current);
    current = next;
  }

  free(node);
}

void free_syllable(Syllable *syll) { free(syll); }

void cleanup_word_lists(void) {
  for (int i = 0; i <= ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;
    while (current != NULL) {
      WordNode *next = current->next;
      free_word_node(current);
      current = next;
    }
    g_word_lists[i].head = NULL;
  }
}

/* Node initialization */

void initialize_word_node(WordNode *node) {
  if (node == NULL || node->original_word == NULL) {
    return;
  }

  node->clean_word = remove_slashes(node->original_word);
  if (node->clean_word == NULL) {
    return;
  }

  node->char_count = count_characters(node->clean_word);
  node->consonant_count = count_consonants(node->clean_word);
  node->vowel_count = count_vowels(node->clean_word);
  node->syllable_count = count_syllables(node->original_word);
  node->syllables = parse_syllables(node->original_word);
  node->is_alphabetically_ordered =
      is_word_alphabetically_ordered(node->clean_word);
  node->alphabetically_sorted = sort_word_alphabetically(node->clean_word);
}

/* Display operations */

void print_word_details(const WordNode *node) {
  if (node == NULL) {
    return;
  }

  printf("\n=== Word Details ===\n");
  printf("Word:                      %s\n", node->clean_word);
  printf("Character count:           %d\n", node->char_count);
  printf("Consonant count:           %d\n", node->consonant_count);
  printf("Vowel count:               %d\n", node->vowel_count);
  printf("Syllable count:            %d\n", node->syllable_count);
  printf("Syllables:                 ");
  print_syllable_list(node->syllables);
  printf("\n");
  printf("Alphabetically ordered:    %s\n",
         node->is_alphabetically_ordered ? "yes" : "no");
  printf("Alphabetically sorted:     %s\n", node->alphabetically_sorted);

  /* Print relationships */
  printf("\nRelationships:\n");
  printf("  Subword of:              %s\n",
         node->subword_of ? node->subword_of->clean_word : "none");
  printf("  Gerund form (-ing):      %s\n",
         node->ing_form ? node->ing_form->clean_word : "none");
  printf("  Past participle (-ed):   %s\n",
         node->ed_form ? node->ed_form->clean_word : "none");
  printf("  Add one character:       %s\n",
         node->add_one_char ? node->add_one_char->clean_word : "none");
  printf("  Lexically close to:      %s\n",
         node->lexically_close ? node->lexically_close->clean_word : "none");
  printf("  Anagram:                 %s\n",
         node->anagram ? node->anagram->clean_word : "none");
}

/* List operations */

void insert_word_sorted_by_length(WordNode **head, const char *word) {
  WordNode *new_node = allocate_word_node();
  if (new_node == NULL) {
    return;
  }

  new_node->original_word = (char *)malloc(strlen(word) + 1);
  if (new_node->original_word == NULL) {
    free_word_node(new_node);
    return;
  }

  strcpy(new_node->original_word, word);
  initialize_word_node(new_node);

  /* Empty list case */
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  /* Insert at beginning if shorter than head */
  if (strlen(new_node->original_word) < strlen((*head)->original_word)) {
    new_node->next = *head;
    (*head)->prev = new_node;
    *head = new_node;
    return;
  }

  /* Find insertion position */
  WordNode *current = *head;
  while (current->next != NULL && strlen(new_node->original_word) >=
                                      strlen(current->next->original_word)) {
    current = current->next;
  }

  /* Insert after current */
  new_node->prev = current;
  new_node->next = current->next;

  if (current->next != NULL) {
    current->next->prev = new_node;
  }

  current->next = new_node;
}

bool delete_word_from_list(WordNode **head, const char *word) {
  if (*head == NULL) {
    return false;
  }

  WordNode *current = *head;
  while (current != NULL && strcmp(current->clean_word, word) != 0) {
    current = current->next;
  }

  if (current == NULL) {
    return false;
  }

  /* Update head if deleting first node */
  if (*head == current) {
    *head = current->next;
  }

  /* Update links */
  if (current->next != NULL) {
    current->next->prev = current->prev;
  }

  if (current->prev != NULL) {
    current->prev->next = current->next;
  }

  free_word_node(current);
  return true;
}

WordNode *search_word(const WordNode *head, const char *word) {
  const WordNode *current = head;
  while (current != NULL) {
    if (strcmp(current->clean_word, word) == 0) {
      return (WordNode *)current;
    }
    current = current->next;
  }
  return NULL;
}

void print_word_list(const WordNode *head) {
  if (head == NULL) {
    printf("(empty)\n");
    return;
  }

  const WordNode *current = head;
  while (current != NULL) {
    printf("%s", current->clean_word);
    if (current->next != NULL) {
      printf(" - ");
    }
    current = current->next;
  }
  printf("\n");
}

void print_all_word_lists(void) {
  printf("\n=== Word Lists ===\n\n");

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (g_word_lists[i].head != NULL) {
      printf("[%c]: ", 'A' + i);
      print_word_list(g_word_lists[i].head);
    }
  }
}

void remove_duplicate_words(void) {
  for (int i = 0; i <= ALPHABET_SIZE; i++) {
    WordNode *current = g_word_lists[i].head;

    while (current != NULL) {
      WordNode *checker = current->next;

      while (checker != NULL) {
        WordNode *next = checker->next;

        if (strcmp(current->clean_word, checker->clean_word) == 0) {
          /* Remove duplicate */
          if (checker->prev != NULL) {
            checker->prev->next = checker->next;
          }
          if (checker->next != NULL) {
            checker->next->prev = checker->prev;
          }
          free_word_node(checker);
        }

        checker = next;
      }

      current = current->next;
    }
  }
}