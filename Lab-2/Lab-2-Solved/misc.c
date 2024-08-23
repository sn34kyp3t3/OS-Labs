#include "misc.h"
#include "DEPARTMENT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **database_creation(FILE *file, int database, int queries) {

  char **tokens = (char **)malloc(sizeof(char *) * database);

  if (!tokens) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }

  int i = 0;

  for (; i < database / 2; i++) {
    tokens[i] = (char *)malloc(BUFFER_SIZE * sizeof(char));
    fscanf(file, "%s/n", tokens[i]);
  }

  char buffer[BUFFER_SIZE];

  for (int j = 0; j < queries; j++) {
    fscanf(file, "%s\n", buffer);
  }

  for (; i < database; i++) {
    tokens[i] = (char *)malloc(BUFFER_SIZE * sizeof(char));
    fscanf(file, "%s/n", tokens[i]);
  }

  return tokens;
}

char **load_queries(FILE *file, int queries, int database) {

  char **queries_tokens = (char **)malloc(sizeof(char *) * queries);

  if (!queries_tokens) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_SET);

  char buffer[BUFFER_SIZE];

  fscanf(file, "%d\n%d\n", &database, &queries);
  for (int i = 0; i < database / 2; i++) {
    fscanf(file, "%s\n", buffer);
  }

  // read querires
  for (int i = 0; i < queries; i++) {
    queries_tokens[i] = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    fscanf(file, "%s\n", queries_tokens[i]);
  }

  return queries_tokens;
}

void query_parser(FILE *output, int queries, char **tokens,
                  char **queries_tokens, int num_tokens) {

  department dept;

  for (int i = 0; i < queries; i++) {

    dept.name = queries_tokens[i];

    search_department(tokens, num_tokens, &dept);

    letter_transform(&dept);

    fprintf(output, "Query number %d:\n", i);
    fprintf(output, "Query number %s:\n", dept.name);

    if (dept.id != -1) {
      fprintf(output, "Department ID: %d\n", dept.id);
    } else {
      fprintf(output, "Department ID: -1\n");
    }

    fprintf(output, "Transformed name: %s\n\n", dept.transformed_name);

    free(dept.transformed_name);
  }
}
