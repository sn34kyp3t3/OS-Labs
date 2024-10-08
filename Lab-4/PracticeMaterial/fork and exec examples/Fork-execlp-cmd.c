/****************************************************************
 *
 *    Example: to demonstrate fork() and execl() system calls
 *
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *cmd[]) {
  pid_t my_pid, parent_pid, child_pid;
  int status;
  /* get and print my pid and my parent's pid. */

  my_pid = getpid();
  parent_pid = getppid();
  printf("\n Parent: my pid is %d\n\n", my_pid);
  printf("Parent: my parent's pid is %d\n\n", parent_pid);

  /* print error message if fork() fails */
  if ((child_pid = fork()) < 0) {
    perror("fork failure");
    exit(1);
  }

  /* fork() == 0 for child process */

  if (child_pid == 0) {
    printf("\nChild: I am a new-born process!\n\n");
    my_pid = getpid();
    parent_pid = getppid();
    printf("Child: my pid is: %d\n\n", my_pid);
    printf("Child: my parent's pid is: %d\n\n", parent_pid);
    execlp(cmd[1], cmd[1], NULL);
    perror("execl() failure!\n\n");

    printf("This print is after execl() and should not have been executed if "
           "execl were successful! \n\n");

    _exit(1);
  }
  /*
   * parent process
   */
  else {
    printf("\nParent: I created a child process.\n\n");
    printf("Parent: my child's pid is: %d\n\n", child_pid);
    wait(&status); /* can use wait(NULL) since exit status
                      from child is not used. */
    printf("\n Parent: my child is dead. I am going to leave.\n \n ");
  }

  return 0;
}
