/* forkexec: create a new process. */
/*  The child runs "ls -aF /". The parent wakes up after 5 seconds */

#include <stdio.h>  /* needed for printf() */
#include <stdlib.h> /* needed to define exit() */
#include <unistd.h> /* needed for fork() and getpid() */

int main(int argc, char **argv) {
  void runit(void);
  int pid; /* process ID */

  switch (pid = fork()) {
  case 0: /* a fork returns 0 to the child */
    runit();
    break;

  default:    /* a fork returns a pid to the parent */
    sleep(5); /* sleep for 5 seconds */
    printf("I'm still here!\n");
    break;

  case -1: /* something went wrong */
    perror("fork");
    exit(1);
  }
  exit(0);
}

void runit(void) {
  printf("About to run ls\n");
  execlp("ls", "ls", "-aF", "/", (char *)0);
  // execlp("/bin/ls","ls", "-aF",NULL);
  perror("execlp"); /* if we get here, execlp failed */
  exit(1);
}
