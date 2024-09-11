#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "misc.h"

int main()
{
    int **A, **B, **C;
    int n, m, q;
    int i, j;

    // Read matrices from files
    if (read_matrix(&A, &n, &m, "matrix1.txt") != 0 ||
        read_matrix(&B, &m, &q, "matrix2.txt") != 0)
    {
        exit(1);
    }

    // Allocate memory for result matrix
    C = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; ++i)
    {
        C[i] = (int *)malloc(q * sizeof(int));
    }

    // Create child processes to calculate elements
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < q; ++j)
        {
            pid_t child_pid = fork();
            if (child_pid == 0)
            {
                // Child process
                int result = calculate_element(A, B, i, j, m);
                exit(result);
            }
            else if (child_pid > 0)
            {
                // Parent process
                int status;
                waitpid(child_pid, &status, 0);
                if (WIFEXITED(status))
                {
                    C[i][j] = WEXITSTATUS(status);
                }
            }
            else
            {
                perror("fork");
                exit(1);
            }
        }
    }

    // Write result matrix to file
    write_matrix(C, n, q, "output.txt");

    // Free memory
    // ... (same as in the template)

    // Free allocated memory
    for (int i = 0; i < n; ++i)
    {
        free(C[i]);
    }
    free(C);

    for (int i = 0; i < n; ++i)
    {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < m; ++i)
    {
        free(B[i]);
    }
    free(B);

    return 0;
}
