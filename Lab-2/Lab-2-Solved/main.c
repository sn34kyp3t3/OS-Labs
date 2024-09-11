#include "DEPARTMENT.h"
#include "misc.h"
// #include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////implement all the drDEPARTMENTiver functions in the misc.c file
//// implement all the department functions in department.c file

int main() {
  FILE *file;
  char buffer[BUFFER_SIZE];
  file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  int database;
  int queries;
  fscanf(file, "%d\n%d\n", &database, &queries);
  printf("Database: %d\nQueries: %d\n", database, queries);

  // implement the following functions
  // database creation from the file
  // load queries from the file

  char **tokens = database_creation(file, database, queries);
  char **queries_tokens = load_queries(file, queries, database);

  fclose(file);
  printf("database is as follows\n");

  for (int i = 0; i < database; i++) {
    printf("%s\n", tokens[i]);
  }
  printf("queries are as follows\n");

  for (int i = 0; i < queries; i++) {
    printf("%s\n", queries_tokens[i]);
  }

  FILE *output = fopen("output.txt", "w");
  // implement the following function
  // query parser and it would also go in the misc.c file

  query_parser(output, queries, tokens, queries_tokens, database);

  fclose(output);
  printf("Lab completed\n");
  return EXIT_SUCCESS;
}
