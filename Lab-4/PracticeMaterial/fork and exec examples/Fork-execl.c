/****************************************************************
 *
 *    Example: to demonstrate fork() and execl() and system calls
 *
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *env[]) {
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
    printf(
        "Child: I will sleep 3 seconds and then execute - date - command \n\n");

    sleep(3);
    printf("Child: Now, I woke up and am executing date command \n\n");
    // execl("/bin/date", "date", NULL);/* execl("/bin/date","date",0,0); */
    execlp("date", "date", NULL); /* execlp("date","date",0,0);
     perror("execl() failure!\n\n");

     printf("This print is after execl() and should not have been executed if
     execl were successful! \n\n");

     _exit(1);*/
  }
  /*
   * parent process
   */
  else {
    printf("\nParent: I created a child process.\n\n");
    printf("Parent: my child's pid is: %d\n\n", child_pid);
    system("ps -el | grep wait");
    printf("\n \n");
    wait(&status); /* can use wait(NULL) since exit status
                      from child is not used. */
    printf("\n Parent: my child is dead. I am going to leave.\n \n ");
  }

  return 0;
}
/*
 *  Parent: my pid is 2020
 *
 *  Parent: my parent's pid is 1740
 *
 *
 *  Parent: I created a child process.
 *
 *  Parent: my child's pid is: 2021
 *
 *
 *  Child: I am a new-born process!
 *
 *  Child: my pid is: 2021
 *
 *  Child: my parent's pid is: 2020
 *
 *  Child: I will sleep 3 seconds and then execute - date - command
 *
 *  1 S     0   996     1  0  80   0 - 29038 wait   ?        00:00:00 ksmtuned
 *  0 S   500  1740  1734  0  80   0 - 29105 wait   pts/0    00:00:00 bash
 *  0 S   500  2020  1740  0  80   0 -   998 wait   pts/0    00:00:00 a.out
 *  0 S   500  2022  2020  0  80   0 - 28512 wait   pts/0    00:00:00 sh
 *
 *
 *   Child: Now, I woke up and am executing date command
 *
 *   Tue Aug 27 09:07:37 IST 2013
 *
 *    Parent: my child is dead. I am going to leave.
 */
