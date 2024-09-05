#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_matrix(int ***matrix, int *rows, int *cols, const char *filename);
int write_matrix(int **matrix, int rows, int cols, const char *filename);
int calculate_element(int **A, int **B, int i, int j, int m);

#endif