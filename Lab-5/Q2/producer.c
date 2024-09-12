#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHARED_MEM_SIZE 1024
#define MAX_LINES 100
#define MAX_LINE_SIZE 50
#define BUFFER_SIZE 3

int main()
{
    key_t keyBuffer = 67, keyIn = 99, keyOut1 = 88, keyOut2 = 77;
    int shmidBuffer, shmidIn, shmidOut1, shmidOut2;
    char(*buffer)[MAX_LINE_SIZE];
    int *in, *out1, *out2;

    if ((shmidBuffer = shmget(keyBuffer, SHARED_MEM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    if ((shmidIn = shmget(keyIn, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    if ((shmidOut1 = shmget(keyOut1, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }
    if ((shmidOut2 = shmget(keyOut2, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    buffer = (char(*)[MAX_LINE_SIZE])shmat(shmidBuffer, NULL, 0);
    in = (int *)shmat(shmidIn, NULL, 0);
    out1 = (int *)shmat(shmidOut1, NULL, 0);
    out2 = (int *)shmat(shmidOut2, NULL, 0);

    *in = *out1 = *out2 = 0; 

    char userInput[MAX_LINE_SIZE];

    while (1)
    {
        fgets(userInput, MAX_LINE_SIZE, stdin);

        while (((*in + 1) % BUFFER_SIZE) == *out1 && ((*in + 1) % BUFFER_SIZE) == *out2)
        {
            usleep(1000);
        }

        strcpy(buffer[*in], userInput);

        if (strcmp(userInput, "$\n") == 0)
        {
            break;
        }

        *in = (*in + 1) % BUFFER_SIZE;
    }

    shmdt(buffer);
    shmdt(in);
    shmdt(out1);
    shmdt(out2);

    shmctl(shmidBuffer, IPC_RMID, NULL);
    shmctl(shmidIn, IPC_RMID, NULL);
    shmctl(shmidOut1, IPC_RMID, NULL);
    shmctl(shmidOut2, IPC_RMID, NULL);

    printf("Producer pid: %d exiting\n", getpid());

    return 0;
}
