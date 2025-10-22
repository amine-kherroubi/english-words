/**
 * User Interface Module
 * Handles all user interaction and display
 */

#ifndef UI_H
#define UI_H

#include "english_words.h"

/* Menu choices */
typedef enum {
  MENU_PRINT_WORD_DATA = 0,
  MENU_PRINT_SUBWORDS = 1,
  MENU_PRINT_VERB_FORMS = 2,
  MENU_PRINT_ADD_ONE_CHAR = 3,
  MENU_PRINT_LEXICALLY_CLOSE = 4,
  MENU_PRINT_ANAGRAMS = 5,
  MENU_INSERT_WORD = 6,
  MENU_DELETE_WORD = 7,
  MENU_PRINT_STATS = 8,
  MENU_EXIT = 9
} MenuChoice;

/* UI functions */
void ui_clear_screen(void);
void ui_wait_for_enter(void);
void ui_display_menu(void);
void ui_main_menu_loop(const Statistics *stats);

/* Menu handlers */
void handle_print_word_data(void);
void handle_print_subwords(int link_count);
void handle_print_verb_forms(int link_count);
void handle_print_add_one_char(void);
void handle_print_lexically_close(int link_count);
void handle_print_anagrams(int link_count);
void handle_insert_word(void);
void handle_delete_word(void);
void handle_print_stats(const Statistics *stats);

#endif /* UI_H */