#include "test.h"
#include "department.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_before_at_after(FILE *fptr) {
  long curr_pos = ftell(fptr); // Get the current position of the file pointer

  // Ensure the file pointer is not at the beginning of the file
  if (curr_pos > 0) {
    // Move to the character before the current position
    fseek(fptr, curr_pos - 1, SEEK_SET);
    printf("Before: %c\n", fgetc(fptr));
  } else {
    printf("Before: N/A (start of file)\n");
  }

  // Move back to the current position
  fseek(fptr, curr_pos, SEEK_SET);
  printf("At: %c\n", fgetc(fptr));

  // Move to the character after the current position
  fseek(fptr, curr_pos + 1, SEEK_SET);
  int after_char = fgetc(fptr);
  if (after_char != EOF) {
    printf("After: %c\n", after_char);
  } else {
    printf("After: N/A (end of file)\n");
  }

  // Restore the original file pointer position
  fseek(fptr, curr_pos, SEEK_SET);
}

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

  // tell the current position in integer.
  /*
  long curr_pos = ftell(file);
  printf("Current file pointer position: %ld\n", curr_pos);
  */

  print_before_at_after(file);

  return 0;
}
