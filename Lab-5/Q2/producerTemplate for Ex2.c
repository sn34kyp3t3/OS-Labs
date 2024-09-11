#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define SHARED_MEM_SIZE 1000
#define MAX_LINES 100
#define MAX_LINE_SIZE 50
#define BUFFER_SIZE 3

int main(int argc, char *argv[])
{
    key_t keyBuffer = 67;
    key_t keyIn = 99;
    key_t keyOut = 88;
    char *shm;
    int shmid;
    int *in;
    int inId;
    int *out;
    int outId;
    char userInput[MAX_LINES][MAX_LINE_SIZE];

    return 0;
}