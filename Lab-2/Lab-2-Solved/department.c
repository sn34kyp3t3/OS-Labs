#include "DEPARTMENT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_newline_with_colon(char *str) {
  while (*str != '\0') {
    if (*str == '\n') {
      *str = ':';
    }
    str++; // str is a pointer so str++ traverses the string.
  }
}

char **tokenize(char *str, const char *delim, int *num_tokens) {

  char **tokens = malloc(MAX_TOKENS * sizeof(char *));
  char *token = strtok(str, delim); // returns a pointer to the first token or
                                    // NULL if no more tokens are found.
  *num_tokens = 0;

  while (token != NULL && *num_tokens < MAX_TOKENS) {
    tokens[*num_tokens] = token;
    (*num_tokens)++;
    token = strtok(NULL, delim);
  }

  return tokens;
}

void search_department(char **tokens, int num_tokens, department *dept) {
  dept->id = -1;

  for (int i = 0; i < num_tokens; i++) {
    if (strcmp(tokens[i], dept->name) == 0) {
      dept->id = i;
      break;
    }
  }
}

void letter_transform(department *dept) {
  int len = strlen(dept->name);
  dept->transformed_name = malloc((len + 1) * sizeof(char));

  if (dept->id != -1) { // If department is found
    dept->transformed_name[0] = tolower(dept->name[0]);
    for (int i = 1; i < len; i++) {
      dept->transformed_name[i] = toupper(dept->name[i]);
    }
  } else { // If department is not found
    for (int i = 0; i < len / 2; i++) {
      dept->transformed_name[i] = dept->name[len / 2 - i - 1];
    }
    strcpy(dept->transformed_name + len / 2,
           dept->name +
               len / 2); // remember dept is a pointer so dept->transformed_name
                         // + len/2 points to the an index in the actual array
                         // => &(dept->transformed_name)
  }
  dept->transformed_name[len] = '\0';
}
