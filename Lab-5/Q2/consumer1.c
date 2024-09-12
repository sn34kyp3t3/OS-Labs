#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 50
#define BUFFER_SIZE 3

int main()
{
    key_t keyBuffer = 67, keyIn = 99, keyOut1 = 88;
    int shmidBuffer, shmidIn, shmidOut1;
    char(*buffer)[MAX_LINE_SIZE];
    int *in, *out1;
    int totalWords = 0;

    shmidBuffer = shmget(keyBuffer, 0, 0666);
    shmidIn = shmget(keyIn, sizeof(int), 0666);
    shmidOut1 = shmget(keyOut1, sizeof(int), 0666);

    buffer = (char(*)[MAX_LINE_SIZE])shmat(shmidBuffer, NULL, 0);
    in = (int *)shmat(shmidIn, NULL, 0);
    out1 = (int *)shmat(shmidOut1, NULL, 0);

    while (1)
    {
        if (*in == *out1)
        {
            usleep(1000); 
        }
        else
        {
            char line[MAX_LINE_SIZE];
            strcpy(line, buffer[*out1]);

            if (strcmp(line, "$\n") == 0)
            {
                break;
            }

            int wordCount = 0;
            char *token = strtok(line, " ");
            while (token != NULL)
            {
                wordCount++;
                token = strtok(NULL, " ");
            }

            totalWords += wordCount;
            printf("Consumer1 pid: %d, number of words in line: %d\n", getpid(), wordCount);
            *out1 = (*out1 + 1) % BUFFER_SIZE;
        }
    }

    printf("Consumer1 pid: %d, total number of words: %d\n", getpid(), totalWords);

    shmdt(buffer);
    shmdt(in);
    shmdt(out1);

    return 0;
}
