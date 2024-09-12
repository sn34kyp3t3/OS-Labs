#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHARED_MEM_SIZE 1000
#define LINE_SIZE 100

int count_words(const char *line)
{
    int count = 0;
    const char *p = line;

    while (*p)
    {
        while (*p && *p == ' ')
            p++;
        if (*p)
            count++;
        while (*p && *p != ' ')
            p++;
    }
    return count;
}

int main()
{
    key_t key = 1234; // Shared memory key
    int shmid;
    char *shm;
    int total_words = 0;

    // Attach to shared memory segment
    shmid = shmget(key, SHARED_MEM_SIZE, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
    shm = (char *)shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    while (1)
    {
        // Wait for a line to be ready
        while (shm[0] != '#')
        {
            usleep(1000); // Sleep for 1000 microseconds
        }

        // Process the line
        int num_words = count_words(shm + 1);
        printf("Consumer pid: %d, number of words in line %d: %d\n", getpid(), total_words + 1, num_words);
        total_words += num_words;

        // Mark the memory with '%'
        shm[0] = '%';

        // Check for end of input
        if (shm[1] == '$')
        {
            break;
        }
    }

    // Print the total number of words
    printf("Consumer pid: %d, total number of words: %d\n", getpid(), total_words);

    // Detach shared memory
    shmdt(shm);

    return 0;
}
