/**
 * Verb Form Generation
 * Generate -ing and -ed forms of verbs
 */

#include "english_words.h"
#include <stdlib.h>
#include <string.h>

char *generate_ing_form(const char *verb) {
  int len = strlen(verb);
  char *ing_form = (char *)malloc(len + 5); /* Extra space for safety */

  if (ing_form == NULL) {
    return NULL;
  }

  /* Special case: "be" -> "being" */
  if (strcmp(verb, "be") == 0) {
    strcpy(ing_form, "being");
    return ing_form;
  }

  /* If verb ends with 'e' */
  if (verb[len - 1] == 'e') {
    if (len >= 2 && verb[len - 2] == 'e') {
      /* Ends with "ee": just add "ing" */
      strcpy(ing_form, verb);
      strcat(ing_form, "ing");
    } else {
      /* Replace 'e' with "ing" */
      strncpy(ing_form, verb, len - 1);
      ing_form[len - 1] = '\0';
      strcat(ing_form, "ing");
    }
  }
  /* If verb ends with consonant-vowel-consonant (CVC) pattern */
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
  int len = strlen(verb);
  char *ed_form = (char *)malloc(len + 5); /* Extra space for safety */

  if (ed_form == NULL) {
    return NULL;
  }

  /* Irregular verbs */
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

  /* Verbs that don't change (cut, put, let, read) */
  if (strcmp(verb, "read") == 0 || strcmp(verb, "cut") == 0 ||
      strcmp(verb, "put") == 0 || strcmp(verb, "let") == 0) {
    strcpy(ed_form, verb);
    return ed_form;
  }

  /* If verb ends with consonant-vowel-consonant (CVC) pattern */
  if (len >= 3 && is_consonant(verb[len - 1]) && is_vowel(verb[len - 2]) &&
      is_consonant(verb[len - 3])) {
    /* Double the last consonant and add "ed" */
    strcpy(ed_form, verb);
    ed_form[len] = verb[len - 1];
    ed_form[len + 1] = '\0';
    strcat(ed_form, "ed");
  }
  /* If verb already ends with "ed" */
  else if (len >= 2 && verb[len - 1] == 'd' && verb[len - 2] == 'e') {
    strcpy(ed_form, verb);
  }
  /* If verb ends with 'e' */
  else if (verb[len - 1] == 'e') {
    strcpy(ed_form, verb);
    strcat(ed_form, "d");
  }
  /* If verb ends with consonant + 'y' */
  else if (len >= 2 && verb[len - 1] == 'y' && is_consonant(verb[len - 2])) {
    strncpy(ed_form, verb, len - 1);
    ed_form[len - 1] = '\0';
    strcat(ed_form, "ied");
  } else {
    /* Default: just add "ed" */
    strcpy(ed_form, verb);
    strcat(ed_form, "ed");
  }

  return ed_form;
}