//
// Created by malho on 09-08-2024.
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_TOKENS 100

typedef struct {
  char *name;
  int id;
  char *transformed_name;
} department;

void replace_newline_with_colon(char *str) {
  while (*str != '\0') {
    if (*str == '\n') {
      *str = ':';
    }
    str++;
  }
}

char **tokenize(char *str, const char *delim, int *num_tokens) {

  char **tokens = malloc(MAX_TOKENS * sizeof(char *));
  *num_tokens = 0;
  char *token = strtok(str, delim);

  while (token != NULL && *num_tokens < MAX_TOKENS) {
    tokens[*num_tokens] = strdup(token);
    // it's important to not assign token instead of strdup(token)
    (*num_tokens)++;
    token = strtok(NULL, delim);
  }
  return tokens;
}

void search_department(char **tokens, int num_tokens, department *dept) {

  for (int i = 0; i < num_tokens; i++) {
    if (strcmp(tokens[i], dept->name) == 0) {
      dept->id = i;
      return;
    }
  }
  dept->id = -1;
}

void letter_transform(department *dept) {
  dept->transformed_name = strdup(dept->name);
  for (int i = 0; dept->transformed_name[i]; i++) {
    dept->transformed_name[i] = toupper(dept->transformed_name[i]);
  }
}

void reverse_first_half(department *dept) {
  int len = strlen(dept->name);
  int mid = len / 2;
  dept->transformed_name = strdup(dept->name);
  for (int i = 0; i < mid; i++) {
    dept->transformed_name[i] = dept->name[mid - i - 1];
  }
  for (int i = mid; i < len; i++) {
    dept->transformed_name[i] = dept->name[i];
  }
}

int main() {
  FILE *file;
  char buffer[BUFFER_SIZE];
  file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  char test[1024];
  memset(test, 0, sizeof(test));
  while (fgets(buffer, BUFFER_SIZE, file)) {
    // Replace newline characters with colons
    replace_newline_with_colon(buffer);
    strcat(test, buffer);
  }
  printf("%s\n", test);
  // Close the file
  fclose(file);
  int num_tokens;
  char **tokens = tokenize(test, ":", &num_tokens);

  // Print the tokens
  for (int i = 0; i < num_tokens; i++) {
    printf("Token %d: %s\n", i + 1, tokens[i]);
  }
  printf("Please enter the department name: ");
  department dept;
  char department_name[100];
  memset(department_name, 0, sizeof(department_name));
  scanf("%s", department_name);
  dept.name = department_name;
  search_department(tokens, num_tokens, &dept);
  int index = dept.id;
  if (index == -1) {
    dept.id = -1;
    // printf("Department not found\n");
    reverse_first_half(&dept);
  } else {
    dept.id = index;
    // printf("Department found at index %d\n", index);
    letter_transform(&dept);
  }
  printf("Department name: %s\n", dept.name);
  printf("Department ID: %d\n", dept.id);
  printf("Transformed name: %s\n", dept.transformed_name);
  free(tokens);

  printf("Lab completed\n");
  return EXIT_SUCCESS;
}
