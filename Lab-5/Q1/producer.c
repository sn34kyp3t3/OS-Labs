#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHARED_MEM_SIZE 1000
#define LINE_SIZE 100

int main()
{
    key_t key = 1234; // Shared memory key
    int shmid;
    char *shm;
    char line[LINE_SIZE];
    int num_lines, i;

    // Create shared memory segment
    shmid = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory segment
    shm = (char *)shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Read the number of lines
    printf("Enter the number of lines: ");
    fgets(line, sizeof(line), stdin);
    num_lines = atoi(line);

    printf("Number of lines: %d\n", num_lines);

    for (i = 0; i < num_lines; i++)
    {
        // Clear shared memory
        memset(shm, 0, SHARED_MEM_SIZE);

        // Read a line from stdin
        printf("Line %d input: ", i + 1);
        fgets(line, sizeof(line), stdin);

        // Copy line to shared memory
        strncpy(shm + 1, line, LINE_SIZE - 1);

        // Mark the memory with '#'
        shm[0] = '#';

        // Wait for consumer to process the line
        while (shm[0] != '%')
        {
            usleep(1000); // Sleep for 1000 microseconds
        }

        // Reset the mark
        shm[0] = 0;
    }

    // Mark the end of input
    shm[0] = '$';

    // Detach and destroy shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);

    printf("Producer pid: %d exiting\n", getpid());

    return 0;
}
