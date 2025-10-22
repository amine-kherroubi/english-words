/**
 * English Words Analysis Program
 * Analyzes English words and creates relationships between them
 */

#include "english_words.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char filename[MAX_FILENAME_LENGTH];

  ui_clear_screen();
  puts("English Words Analysis Program");
  puts("==============================\n");
  printf("Enter the path to the word list file: ");
  fflush(stdout);

  if (fgets(filename, sizeof(filename), stdin) == NULL) {
    puts("Error reading filename.");
    return EXIT_FAILURE;
  }

  /* Remove trailing newline if present */
  size_t len = strlen(filename);
  if (len > 0 && filename[len - 1] == '\n') {
    filename[len - 1] = '\0';
  }

  ui_clear_screen();

  /* Load words from file */
  int word_count = load_words_from_file(filename);
  if (word_count == -1) {
    printf("Error: Unable to open file '%s'.\n", filename);
    return EXIT_FAILURE;
  }

  /* Remove duplicate words */
  remove_duplicate_words();

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