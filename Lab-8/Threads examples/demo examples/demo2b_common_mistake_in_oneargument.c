#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

/*
//  The thread_function is to print a single integer value.
The pthread_create() imposes a strict format on the prototype of the function that will run in the new thread. It must take a single void* parameter and return a single void* value. The last parameter of pthread_create() is passed as the argument to the function, whereas the return value is passed using pthread_exit() and pthread_join(). 
*/
void * thread_function (void *_args)
{
/*
/* POTENTIALLY DANGEROUS TIMING 
  int *argptr = (int *) args;
  int arg = *argptr;
 Bug Warning

Casting integral values to pointers and back again is a common practice for passing parameters to pthreads. However, while it is generally safe in practice, it is potentially a bug on some platforms. Specifically, this technique relies on the fact that pointers are at least as large as standard integer types. That is, int variables are typically (but not required to be) 32 bits in size. Modern CPU architectures tend to use 32- or 64-bit addresses. As such, casting a 32-bit int up to a void* then back to a 32-bit int is safe.

On the other hand, assume the argument was declared as a long variable instance. If the code is running on a 32-bit architecture (which is not uncommon for virtualized systems) but the long type is 64 bits in size, then half of the argument is lost by down-casting to the pointer for the call to pthread_create()! 
*/
  /* Safe whenever size of int <= size of pointer (which is
     usually true) */
  //int arg = (int) _args; //error
  long arg = (long) _args;
/* Convention: It is common to name a void* parameter with a name
   that begins with _, then cast it to a local variable that has
   the same (or nearly the same) name without the _. So _args will
   become args. Recall that _ has no special meaning and is treated
   like a normal alphabetical character. */

  /* Print the local copy of the argument */
  printf ("Argument is %ld\n", arg);
  pthread_exit (NULL);
}

int main()
{
pthread_t threads[NUM_THREADS];
/* 
   Passing a pointer to a variable that repeatedly changes is a common error with threads
 */

/* BAD CODE - DON'T DO THIS */
/* What value is actually passed to the thread? 
for (int i = 1; i <= 10; i++)
     pthread_create (&child[i], NULL, child_thread, &i);
  The key problem is that thread creation and execution is asynchronous. That means that it is impossible to predict when each of the new threads start running. One possible timing is that all 10 threads are created first, leading to i storing the value 11. At that point, each of the threads dereference their respective argptr variable and all get the same value of 11.

One common solution to this problem is to cast numeric values as pointers, as shown below. That is, the int i variable gets cast as a (void*) argument in the call to pthread_create(). Then, the void* argument to child_thread() casts the argument back to a int instance.
/* 
   Each thread should be given a separate value, rather than a shared address
 */

/* FIXED VERSION */
/* ints are passed by value, so a COPY gets passed to each call */
for (long i = 0; i < NUM_THREADS; i++)
  pthread_create (&threads[i], NULL, thread_function, (void *)i);
    
/*  
What makes this code work is the fact that scalar variables (e.g., int variables) are passed using call-by-value semantics. When this code prepares for the pthread_create() call, a separate copy of the current value of the i variable is placed into a register or onto the stack. The child_thread() function then gets this copy, regardless of any changes to the original i variable. When the child thread then casts its args parameter to a local arg_value, it is working with the correct value that was passed.
*/
return 0;
}

