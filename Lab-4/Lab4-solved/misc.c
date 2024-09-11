#include <stdio.h>
#include <stdlib.h>
#include "misc.h"
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SIZE 100

// Function to read a matrix from a file
int read_matrix(int ***matrix, int *rows, int *cols, const char *filename)
{
    FILE *fp;
    int i, j;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fscanf(fp, "%d %d", rows, cols);

    *matrix = (int **)malloc(*rows * sizeof(int *));
    for (i = 0; i < *rows; ++i)
    {
        (*matrix)[i] = (int *)malloc(*cols * sizeof(int));
        for (j = 0; j < *cols; ++j)
        {
            fscanf(fp, "%d", &(*matrix)[i][j]);
        }
    }

    fclose(fp);
    return 0;
}

// Function to write a matrix to a file
int write_matrix(int **matrix, int rows, int cols, const char *filename)
{
    FILE *fp;
    int i, j;

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fprintf(fp, "%d %d\n", rows, cols);
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            fprintf(fp, "%d ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}

// Function to calculate a single element of the result matrix
int calculate_element(int **A, int **B, int i, int j, int m)
{
    int sum = 0;
    int k;

    for (k = 0; k < m; ++k)
    {
        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            // Child process
            int product = A[i][k] * B[k][j];
            printf("Level 3 Process PID %d: Computed %d * %d = %d\n", getpid(), A[i][k], B[k][j], product);
            exit(product);
        }
        else if (child_pid > 0)
        {
            // Parent process
            int status;
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status))
            {
                sum += WEXITSTATUS(status);
            }
        }
        else
        {
            perror("fork");
            exit(1);
        }
    }
    printf("Level 2 Process PID %d: Sum for C[%d][%d] = %d\n", getpid(), i, j, sum);

    return sum;
}