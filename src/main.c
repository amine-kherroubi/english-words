/**
 * English Words Analysis Program
 * Analyzes English words and creates relationships between them
 *
 * Updated for new project structure
 */

#include "../include/english_words.h"
#include "../include/ui.h"
#include <stdio.h>
#include <stdlib.h>

#define WORDS_FILE "../data/words.txt"

int main(void) {
  ui_clear_screen();
  puts("English Words Analysis Program");
  puts("==============================\n");
  printf("Loading words from %s...\n", WORDS_FILE);

  /* Load words from file */
  int word_count = load_words_from_file(WORDS_FILE);
  if (word_count == -1) {
    printf("Error: Unable to open file '%s'.\n", WORDS_FILE);
    printf("Make sure the file exists in the data directory.\n");
    printf("Current working directory should be: build/bin/\n");
    return EXIT_FAILURE;
  }

  printf("Loaded %d words.\n", word_count);

  /* Remove duplicate words */
  remove_duplicate_words();

  printf("Building relationships...\n");

  /* Create word relationships */
  int subword_links = create_subword_links();
  int verb_form_links = create_verb_form_links();
  int lexclose_links = create_lexically_close_links();
  int anagram_links = create_anagram_links();

  /* Store statistics */
  Statistics stats = {.word_count = word_count,
                      .subword_links = subword_links,
                      .verb_form_links = verb_form_links,
                      .lexclose_links = lexclose_links,
                      .anagram_links = anagram_links};

  /* Display initial word lists */
  print_all_word_lists();

  /* Main menu loop */
  ui_wait_for_enter();
  ui_main_menu_loop(&stats);

  /* Cleanup */
  cleanup_word_lists();

  ui_clear_screen();
  puts("Program terminated.");

  return EXIT_SUCCESS;
}