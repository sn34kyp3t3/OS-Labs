// misc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"

void read_line_from_file(const char *filename, int line_number, char *buffer)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int current_line = 0;
    while (fgets(buffer, 256, file))
    {
        if (current_line == line_number)
        {
            break;
        }
        current_line++;
    }

    fclose(file);

    // Remove newline character if present
    buffer[strcspn(buffer, "\n")] = '\0';
}
