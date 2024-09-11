#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int var_glb; /* A global variable*/

int main(void) {
  pid_t childPID;
  int var_lcl = 0;

  childPID = fork();

  if (childPID >= 0) // fork was successful
  {
    if (childPID == 0) // child process
    {
      var_lcl++;
      var_glb++;
      printf("\n Child Process :: var_lcl = %d, var_glb= %d\n", var_lcl,
             var_glb);
    } else // Parent process
    {
      var_lcl = 10;
      var_glb = 20;
      printf("\n Parent process :: var_lcl = %d, var_glb= %d\n", var_lcl,
             var_glb);
    }
  } else // fork failed
  {
    printf("\n Fork failed, quitting!!!!!!\n");
    return 1;
  }

  return 0;
}
/*Parent process :: var_lcl = 10, var_glb= 20
 *
 *  Child Process :: var_lcl = 1, var_glb= 1
 */
