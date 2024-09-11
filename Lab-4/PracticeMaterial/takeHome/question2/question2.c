#include "misc.h"
#include "processCreation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // Root process
    printf("Root process: PID = %d, creating P2 and P3\n", getpid());
    create_processes();

    printf("\nRoot process printing lines:\n");

    // Print contents of input.txt
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
