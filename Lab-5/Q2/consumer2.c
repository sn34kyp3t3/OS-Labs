#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define SHARED_MEM_SIZE 1024
#define MAX_LINE_SIZE 50
#define BUFFER_SIZE 3

int count_capital_letters(char *line)
{
    int count = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (isupper(line[i]))
        {
            count++;
        }
    }
    return count;
}

int main()
{
    key_t keyBuffer = 67;
    key_t keyIn = 99;
    key_t keyOut2 = 88;

    int shmidBuffer = shmget(keyBuffer, SHARED_MEM_SIZE, 0666);
    if (shmidBuffer < 0)
    {
        perror("shmget");
        exit(1);
    }
    char(*buffer)[MAX_LINE_SIZE] = shmat(shmidBuffer, NULL, 0);

    int shmidIn = shmget(keyIn, sizeof(int), 0666);
    if (shmidIn < 0)
    {
        perror("shmget in");
        exit(1);
    }
    int *in = shmat(shmidIn, NULL, 0);

    int shmidOut2 = shmget(keyOut2, sizeof(int), 0666);
    if (shmidOut2 < 0)
    {
        perror("shmget out2");
        exit(1);
    }
    int *out2 = shmat(shmidOut2, NULL, 0);

    int totalCapitalLetters = 0;

    while (1)
    {
        if (*out2 == *in)
        {
            usleep(1000);
            continue;
        }

        char *line = buffer[*out2];

        if (line[0] == '$' && line[1] == '\n')
        {
            printf("Consumer pid: %d, total number of capital letters: %d\n", getpid(), totalCapitalLetters);
            break;
        }

        int capitalLetters = count_capital_letters(line);
        printf("Consumer pid: %d, number of capital letters in line %d: %d\n", getpid(), *out2 + 1, capitalLetters);
        totalCapitalLetters += capitalLetters;

        *out2 = (*out2 + 1) % BUFFER_SIZE;
    }

    shmdt(buffer);
    shmdt(in);
    shmdt(out2);

    return 0;
}
