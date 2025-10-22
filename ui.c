/**
 * User Interface Implementation
 *
 * Improvements:
 * - Better input validation
 * - More informative error messages
 * - Safer string handling
 */

#include "ui.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void ui_clear_screen(void) {
  int result = system(CLEAR_COMMAND);
  (void)result;
}

void ui_wait_for_enter(void) {
  printf("\nPress ENTER to continue...");
  fflush(stdout);
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void ui_display_menu(void) {
  puts("\n=== Menu Options ===");
  puts("0) Display word details");
  puts("1) Display subword chains");
  puts("2) Display verb forms (ed/ing)");
  puts("3) Display words formed by adding one character");
  puts("4) Display lexically close words");
  puts("5) Display anagrams");
  puts("6) Insert a new word");
  puts("7) Delete a word");
  puts("8) Display statistics");
  puts("9) Exit");
  printf("\nYour choice: ");
  fflush(stdout);
}

static char *read_word_input(const char *prompt) {
  static char input[MAX_WORD_LENGTH + 10];
  static char word[MAX_WORD_LENGTH];

  printf("%s", prompt);
  fflush(stdout);

  if (fgets(input, sizeof(input), stdin) == NULL) {
    return NULL;
  }

  /* Remove trailing whitespace */
  size_t len = strlen(input);
  while (len > 0 && isspace((unsigned char)input[len - 1])) {
    input[--len] = '\0';
  }

  /* Remove leading whitespace */
  char *start = input;
  while (*start && isspace((unsigned char)*start)) {
    start++;
  }

  if (strlen(start) == 0 || strlen(start) >= MAX_WORD_LENGTH) {
    return NULL;
  }

  strncpy(word, start, MAX_WORD_LENGTH - 1);
  word[MAX_WORD_LENGTH - 1] = '\0';

  return word;
}

static void handle_print_word_data(Statistics *stats) {
  (void)stats;

  char *word = read_word_input("Enter a word: ");

  if (word == NULL) {
    ui_clear_screen();
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  /* Remove slashes for searching */
  char *clean = remove_slashes(word);
  if (clean == NULL) {
    puts("Error allocating memory.");
    return;
  }

  int index = get_word_letter_index(clean);
  if (index < 0 || index > ALPHABET_SIZE) {
    puts("Invalid word.");
    free(clean);
    return;
  }

  WordNode *node = search_word(g_word_lists[index].head, clean);
  free(clean);

  if (node == NULL) {
    puts("This word does not exist in the dictionary.");
  } else {
    print_word_details(node);
  }
}

static void handle_print_subwords(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Subword Chains ===\n");
    print_subword_chains();
  } else {
    puts("No subword relationships found.");
  }
}

static void handle_print_verb_forms(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Verb Forms (ed/ing) ===\n");
    print_verb_forms();
  } else {
    puts("No verb forms found.");
  }
}

static void handle_print_add_one_char(void) {
  ui_clear_screen();
  puts("Feature not yet implemented.");
}

static void handle_print_lexically_close(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Lexically Close Words ===\n");
    print_lexically_close_words();
  } else {
    puts("No lexically close words found.");
  }
}

static void handle_print_anagrams(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Anagrams ===\n");
    print_anagrams();
  } else {
    puts("No anagrams found.");
  }
}

static void handle_insert_word(Statistics *stats) {
  char *word =
      read_word_input("Enter a word to insert (separate syllables with '/'): ");

  if (word == NULL) {
    ui_clear_screen();
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  /* Validate word format */
  if (!is_valid_word_format(word)) {
    puts("Invalid word format. Word must contain only letters and '/' "
         "separators.");
    return;
  }

  int index = get_word_letter_index(word);
  if (index < 0 || index > ALPHABET_SIZE) {
    puts("Invalid word.");
    return;
  }

  /* Check with clean word */
  char *clean = remove_slashes(word);
  if (clean == NULL) {
    puts("Error allocating memory.");
    return;
  }

  WordNode *existing = search_word(g_word_lists[index].head, clean);
  free(clean);

  if (existing != NULL) {
    puts("This word already exists.");
  } else {
    ErrorCode result =
        insert_word_sorted_by_length(&g_word_lists[index].head, word);

    if (result != SUCCESS) {
      printf("Failed to insert word (error code: %d).\n", result);
      return;
    }

    /* Save to file */
    if (save_word_to_file(word)) {
      puts("Word successfully added and saved to words.txt");

      /* Recalculate relationships */
      printf("Recalculating relationships...\n");
      stats->subword_links = create_subword_links();
      stats->verb_form_links = create_verb_form_links();
      stats->lexclose_links = create_lexically_close_links();
      stats->anagram_links = create_anagram_links();
      stats->word_count++;
      printf("Done!\n");
    } else {
      puts("Word added but failed to save to file.");
    }
  }
}

static void handle_delete_word(Statistics *stats) {
  char *word = read_word_input("Enter a word to delete: ");

  if (word == NULL) {
    ui_clear_screen();
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  /* Remove slashes for searching */
  char *clean = remove_slashes(word);
  if (clean == NULL) {
    puts("Error allocating memory.");
    return;
  }

  int index = get_word_letter_index(clean);
  if (index < 0 || index > ALPHABET_SIZE) {
    puts("Invalid word.");
    free(clean);
    return;
  }

  bool deleted = delete_word_from_list(&g_word_lists[index].head, clean);
  free(clean);

  if (deleted) {
    /* Save all words back to file */
    if (save_all_words_to_file()) {
      puts("Word successfully deleted and changes saved to words.txt");

      /* Recalculate relationships */
      printf("Recalculating relationships...\n");
      stats->subword_links = create_subword_links();
      stats->verb_form_links = create_verb_form_links();
      stats->lexclose_links = create_lexically_close_links();
      stats->anagram_links = create_anagram_links();
      stats->word_count--;
      printf("Done!\n");
    } else {
      puts("Word deleted but failed to save changes to file.");
    }
  } else {
    puts("This word does not exist.");
  }
}

static void handle_print_stats(const Statistics *stats) {
  if (stats == NULL) {
    puts("Error: Statistics not available.");
    return;
  }

  ui_clear_screen();

  puts("=== Statistics ===");
  printf("Total words read:              %d\n", stats->word_count);
  printf("Subword links created:         %d\n", stats->subword_links);
  printf("Verb form links created:       %d\n", stats->verb_form_links);
  printf("Lexically close links created: %d\n", stats->lexclose_links);
  printf("Anagram links created:         %d\n", stats->anagram_links);
}

void ui_main_menu_loop(Statistics *stats) {
  if (stats == NULL) {
    puts("Error: Statistics not provided.");
    return;
  }

  char input[100];
  int choice;

  while (1) {
    ui_display_menu();

    if (fgets(input, sizeof(input), stdin) == NULL) {
      ui_clear_screen();
      puts("Error reading input.");
      print_all_word_lists();
      continue;
    }

    /* Try to parse the choice */
    if (sscanf(input, "%d", &choice) != 1) {
      ui_clear_screen();
      puts("Invalid choice. Please enter a number.");
      print_all_word_lists();
      continue;
    }

    switch (choice) {
    case MENU_PRINT_WORD_DATA:
      handle_print_word_data(stats);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_SUBWORDS:
      handle_print_subwords(stats->subword_links);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_VERB_FORMS:
      handle_print_verb_forms(stats->verb_form_links);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_ADD_ONE_CHAR:
      handle_print_add_one_char();
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_LEXICALLY_CLOSE:
      handle_print_lexically_close(stats->lexclose_links);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_ANAGRAMS:
      handle_print_anagrams(stats->anagram_links);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_INSERT_WORD:
      handle_insert_word(stats);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_DELETE_WORD:
      handle_delete_word(stats);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_PRINT_STATS:
      handle_print_stats(stats);
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_EXIT:
      return;

    default:
      ui_clear_screen();
      puts("Invalid choice. Please try again.");
      print_all_word_lists();
      break;
    }
  }
}