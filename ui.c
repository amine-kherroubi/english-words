/**
 * User Interface Implementation
 */

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void ui_clear_screen(void) { system(CLEAR_COMMAND); }

void ui_wait_for_enter(void) {
  printf("\nPress ENTER to continue...");
  getchar();
  getchar();
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
}

void handle_print_word_data(void) {
  char word[MAX_WORD_LENGTH];
  printf("Enter a word: ");
  if (scanf("%49s", word) != 1) {
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  int index = get_word_letter_index(word);
  WordNode *node = search_word(g_word_lists[index].head, word);

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

void handle_insert_word(void) {
  char word[MAX_WORD_LENGTH];
  printf("Enter a word to insert (separate syllables with '/'): ");
  if (scanf("%49s", word) != 1) {
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  int index = get_word_letter_index(word);
  if (search_word(g_word_lists[index].head, word) != NULL) {
    puts("This word already exists.");
  } else {
    insert_word_sorted_by_length(&g_word_lists[index].head, word);
    puts("Word successfully added.");
  }
}

void handle_delete_word(void) {
  char word[MAX_WORD_LENGTH];
  printf("Enter a word to delete: ");
  if (scanf("%49s", word) != 1) {
    puts("Invalid input.");
    return;
  }

  ui_clear_screen();

  int index = get_word_letter_index(word);
  if (delete_word_from_list(&g_word_lists[index].head, word)) {
    puts("Word successfully deleted.");
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

void ui_main_menu_loop(const Statistics *stats) {
  int choice;

  while (1) {
    ui_display_menu();

    if (scanf("%d", &choice) != 1) {
      /* Clear invalid input */
      while (getchar() != '\n')
        ;
      ui_clear_screen();
      puts("Invalid choice. Please enter a number.");
      print_all_word_lists();
      continue;
    }

    switch (choice) {
    case MENU_PRINT_WORD_DATA:
      handle_print_word_data();
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
      handle_insert_word();
      ui_wait_for_enter();
      ui_clear_screen();
      print_all_word_lists();
      break;

    case MENU_DELETE_WORD:
      handle_delete_word();
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