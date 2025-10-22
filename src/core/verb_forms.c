/**
 * Verb Form Generation
 * Generate -ing and -ed forms of verbs
 *
 * Improvements:
 * - Better buffer size calculations
 * - More comprehensive irregular verb handling
 * - Safer string operations
 */

#include "../../include/english_words.h"
#include <stdlib.h>
#include <string.h>

char *generate_ing_form(const char *verb) {
  if (verb == NULL || verb[0] == '\0') {
    return NULL;
  }

  size_t len = strlen(verb);
  char *ing_form =
      (char *)malloc(len + 8); /* Enough for doubling + "ing" + null */

  if (ing_form == NULL) {
    return NULL;
  }

  /* Special case: "be" -> "being" */
  if (strcmp(verb, "be") == 0) {
    strcpy(ing_form, "being");
    return ing_form;
  }

  /* Special case: "lie" -> "lying" */
  if (strcmp(verb, "lie") == 0) {
    strcpy(ing_form, "lying");
    return ing_form;
  }

  /* Special case: "die" -> "dying" */
  if (strcmp(verb, "die") == 0) {
    strcpy(ing_form, "dying");
    return ing_form;
  }

  /* If verb ends with 'ie', replace with 'ying' */
  if (len >= 2 && verb[len - 2] == 'i' && verb[len - 1] == 'e') {
    strncpy(ing_form, verb, len - 2);
    ing_form[len - 2] = '\0';
    strcat(ing_form, "ying");
  }
  /* If verb ends with 'e' (but not 'ee', 'oe', 'ye') */
  else if (verb[len - 1] == 'e') {
    if (len >= 2 && (verb[len - 2] == 'e' || verb[len - 2] == 'o' ||
                     verb[len - 2] == 'y')) {
      /* Ends with "ee", "oe", or "ye": just add "ing" */
      strcpy(ing_form, verb);
      strcat(ing_form, "ing");
    } else {
      /* Replace 'e' with "ing" */
      strncpy(ing_form, verb, len - 1);
      ing_form[len - 1] = '\0';
      strcat(ing_form, "ing");
    }
  }
  /* CVC pattern: consonant-vowel-consonant (but not w, x, y at end) */
  else if (len >= 3 && verb[len - 1] != 'w' && verb[len - 1] != 'x' &&
           verb[len - 1] != 'y' && is_consonant(verb[len - 1]) &&
           is_vowel(verb[len - 2]) && is_consonant(verb[len - 3])) {
    /* Double the last consonant and add "ing" */
    strcpy(ing_form, verb);
    ing_form[len] = verb[len - 1];
    ing_form[len + 1] = '\0';
    strcat(ing_form, "ing");
  } else {
    /* Default: just add "ing" */
    strcpy(ing_form, verb);
    strcat(ing_form, "ing");
  }

  return ing_form;
}

char *generate_ed_form(const char *verb) {
  if (verb == NULL || verb[0] == '\0') {
    return NULL;
  }

  size_t len = strlen(verb);
  char *ed_form =
      (char *)malloc(len + 8); /* Enough for doubling + "ed" + null */

  if (ed_form == NULL) {
    return NULL;
  }

  /* Common irregular verbs */
  if (strcmp(verb, "be") == 0) {
    strcpy(ed_form, "been");
    return ed_form;
  }
  if (strcmp(verb, "have") == 0) {
    strcpy(ed_form, "had");
    return ed_form;
  }
  if (strcmp(verb, "go") == 0) {
    strcpy(ed_form, "gone");
    return ed_form;
  }
  if (strcmp(verb, "do") == 0) {
    strcpy(ed_form, "done");
    return ed_form;
  }
  if (strcmp(verb, "see") == 0) {
    strcpy(ed_form, "seen");
    return ed_form;
  }
  if (strcmp(verb, "make") == 0) {
    strcpy(ed_form, "made");
    return ed_form;
  }
  if (strcmp(verb, "take") == 0) {
    strcpy(ed_form, "took");
    return ed_form;
  }
  if (strcmp(verb, "find") == 0) {
    strcpy(ed_form, "found");
    return ed_form;
  }
  if (strcmp(verb, "think") == 0) {
    strcpy(ed_form, "thought");
    return ed_form;
  }
  if (strcmp(verb, "teach") == 0) {
    strcpy(ed_form, "taught");
    return ed_form;
  }
  if (strcmp(verb, "grow") == 0) {
    strcpy(ed_form, "grown");
    return ed_form;
  }
  if (strcmp(verb, "drive") == 0) {
    strcpy(ed_form, "drove");
    return ed_form;
  }
  if (strcmp(verb, "wake") == 0) {
    strcpy(ed_form, "woke");
    return ed_form;
  }

  /* Verbs that don't change */
  if (strcmp(verb, "read") == 0 || strcmp(verb, "cut") == 0 ||
      strcmp(verb, "put") == 0 || strcmp(verb, "let") == 0 ||
      strcmp(verb, "hit") == 0 || strcmp(verb, "quit") == 0 ||
      strcmp(verb, "shut") == 0) {
    strcpy(ed_form, verb);
    return ed_form;
  }

  /* If verb already ends with "ed" */
  if (len >= 2 && verb[len - 1] == 'd' && verb[len - 2] == 'e') {
    strcpy(ed_form, verb);
  }
  /* If verb ends with 'e' (not "ee") */
  else if (verb[len - 1] == 'e') {
    if (len >= 2 && verb[len - 2] == 'e') {
      /* Ends with "ee": just add "d" */
      strcpy(ed_form, verb);
      strcat(ed_form, "d");
    } else {
      /* Ends with 'e': just add "d" */
      strcpy(ed_form, verb);
      strcat(ed_form, "d");
    }
  }
  /* If verb ends with consonant + 'y' */
  else if (len >= 2 && verb[len - 1] == 'y' && is_consonant(verb[len - 2])) {
    strncpy(ed_form, verb, len - 1);
    ed_form[len - 1] = '\0';
    strcat(ed_form, "ied");
  }
  /* CVC pattern: consonant-vowel-consonant (but not w, x, y at end) */
  else if (len >= 3 && verb[len - 1] != 'w' && verb[len - 1] != 'x' &&
           verb[len - 1] != 'y' && is_consonant(verb[len - 1]) &&
           is_vowel(verb[len - 2]) && is_consonant(verb[len - 3])) {
    /* Double the last consonant and add "ed" */
    strcpy(ed_form, verb);
    ed_form[len] = verb[len - 1];
    ed_form[len + 1] = '\0';
    strcat(ed_form, "ed");
  } else {
    /* Default: just add "ed" */
    strcpy(ed_form, verb);
    strcat(ed_form, "ed");
  }

  return ed_form;
}