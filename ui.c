/**
 * User Interface Implementation
 */

#include "ui.h"
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
  (void)result; /* Suppress unused variable warning */
}

void ui_wait_for_enter(void) {
  printf("\nPress ENTER to continue...");
  fflush(stdout);
  /* Just wait for a single enter - the buffer should already be clean */
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

void handle_print_word_data(Statistics *stats) {
  (void)stats; /* Unused parameter */
  char word[MAX_WORD_LENGTH];
  char input[MAX_WORD_LENGTH + 10];

  printf("Enter a word: ");
  fflush(stdout);

  if (fgets(input, sizeof(input), stdin) == NULL) {
    puts("Invalid input.");
    return;
  }

  /* Remove trailing newline and extract word */
  size_t len = strlen(input);
  if (len > 0 && input[len - 1] == '\n') {
    input[len - 1] = '\0';
    len--;
  }

  if (len == 0 || len >= MAX_WORD_LENGTH) {
    puts("Invalid word length.");
    return;
  }

  strncpy(word, input, MAX_WORD_LENGTH - 1);
  word[MAX_WORD_LENGTH - 1] = '\0';

  ui_clear_screen();

  /* Remove slashes for searching since clean_word is stored */
  char *clean = remove_slashes(word);
  if (clean == NULL) {
    puts("Error allocating memory.");
    return;
  }

  int index = get_word_letter_index(clean);
  WordNode *node = search_word(g_word_lists[index].head, clean);
  free(clean);

  if (node == NULL) {
    puts("This word does not exist in the dictionary.");
  } else {
    print_word_details(node);
  }
}

void handle_print_subwords(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Subword Chains ===\n");
    print_subword_chains();
  } else {
    puts("No subword relationships found.");
  }
}

void handle_print_verb_forms(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Verb Forms (ed/ing) ===\n");
    print_verb_forms();
  } else {
    puts("No verb forms found.");
  }
}

void handle_print_add_one_char(void) {
  ui_clear_screen();
  puts("Feature not yet implemented.");
}

void handle_print_lexically_close(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Lexically Close Words ===\n");
    print_lexically_close_words();
  } else {
    puts("No lexically close words found.");
  }
}

void handle_print_anagrams(int link_count) {
  ui_clear_screen();

  if (link_count >= 1) {
    puts("=== Anagrams ===\n");
    print_anagrams();
  } else {
    puts("No anagrams found.");
  }
}

void handle_insert_word(Statistics *stats) {
  char word[MAX_WORD_LENGTH];
  char input[MAX_WORD_LENGTH + 10];

  printf("Enter a word to insert (separate syllables with '/'): ");
  fflush(stdout);

  if (fgets(input, sizeof(input), stdin) == NULL) {
    puts("Invalid input.");
    return;
  }

  /* Remove trailing newline and extract word */
  size_t len = strlen(input);
  if (len > 0 && input[len - 1] == '\n') {
    input[len - 1] = '\0';
    len--;
  }

  if (len == 0 || len >= MAX_WORD_LENGTH) {
    puts("Invalid word length.");
    return;
  }

  strncpy(word, input, MAX_WORD_LENGTH - 1);
  word[MAX_WORD_LENGTH - 1] = '\0';

  ui_clear_screen();

  int index = get_word_letter_index(word);

  /* Need to check with clean word since that's what's stored */
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
    insert_word_sorted_by_length(&g_word_lists[index].head, word);

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

void handle_delete_word(Statistics *stats) {
  char word[MAX_WORD_LENGTH];
  char input[MAX_WORD_LENGTH + 10];

  printf("Enter a word to delete: ");
  fflush(stdout);

  if (fgets(input, sizeof(input), stdin) == NULL) {
    puts("Invalid input.");
    return;
  }

  /* Remove trailing newline and extract word */
  size_t len = strlen(input);
  if (len > 0 && input[len - 1] == '\n') {
    input[len - 1] = '\0';
    len--;
  }

  if (len == 0 || len >= MAX_WORD_LENGTH) {
    puts("Invalid word length.");
    return;
  }

  strncpy(word, input, MAX_WORD_LENGTH - 1);
  word[MAX_WORD_LENGTH - 1] = '\0';

  ui_clear_screen();

  /* Remove slashes for searching since clean_word is stored */
  char *clean = remove_slashes(word);
  if (clean == NULL) {
    puts("Error allocating memory.");
    return;
  }

  int index = get_word_letter_index(clean);
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

void handle_print_stats(const Statistics *stats) {
  ui_clear_screen();

  puts("=== Statistics ===");
  printf("Total words read:              %d\n", stats->word_count);
  printf("Subword links created:         %d\n", stats->subword_links);
  printf("Verb form links created:       %d\n", stats->verb_form_links);
  printf("Lexically close links created: %d\n", stats->lexclose_links);
  printf("Anagram links created:         %d\n", stats->anagram_links);
}

void ui_main_menu_loop(Statistics *stats) {
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