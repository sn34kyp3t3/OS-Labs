// processCreation.c
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "processCreation.h"

void create_processes()
{
    pid_t pid;

    // NOTE Forking P2 and P3
    if ((pid = fork()) == 0)
    {
        // NOTE P2
        printf("Process P2: PID = %d, creating P4 and P5\n", getpid());
        if ((pid = fork()) == 0)
        {
            // NOTE P4
            printf("Process P4: PID = %d, creating P8\n", getpid());
            if ((pid = fork()) == 0)
            {
                // NOTE P8
                char buffer[256];
                read_line_from_file("input.txt", 0, buffer);
                printf("Process P8: PID = %d, read line: %s\n", getpid(), buffer);
                exit(0);
            }
            wait(NULL);
            exit(0);
        }

        if ((pid = fork()) == 0)
        {
            // NOTE P5
            char buffer[256];
            read_line_from_file("input.txt", 1, buffer);
            printf("Process P5: PID = %d, read line: %s\n", getpid(), buffer);
            exit(0);
        }
        wait(NULL);
        wait(NULL);
        exit(0);
    }

    if ((pid = fork()) == 0)
    {
        // NOTE P3
        printf("Process P3: PID = %d, creating P6 and P7\n", getpid());
        if ((pid = fork()) == 0)
        {
            // NOTE P6
            char buffer[256];
            read_line_from_file("input.txt", 2, buffer);
            printf("Process P6: PID = %d, read line: %s\n", getpid(), buffer);
            exit(0);
        }

        if ((pid = fork()) == 0)
        {
            // NOTE P7
            printf("Process P7: PID = %d, creating P9 and P10\n", getpid());
            if ((pid = fork()) == 0)
            {
                // NOTE P9
                char buffer[256];
                read_line_from_file("input.txt", 3, buffer);
                printf("Process P9: PID = %d, read line: %s\n", getpid(), buffer);
                exit(0);
            }

            if ((pid = fork()) == 0)
            {
                // NOTE P10
                char buffer[256];
                read_line_from_file("input.txt", 4, buffer);
                printf("Process P10: PID = %d, read line: %s\n", getpid(), buffer);
                exit(0);
            }
            wait(NULL);
            wait(NULL);

            char buffer[256];
            read_line_from_file("input.txt", 5, buffer);
            printf("Process P7: PID = %d, read line: %s\n", getpid(), buffer);
            exit(0);
        }
        wait(NULL);
        wait(NULL);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
}
