#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

struct thread_data
{
   int	thread_id,sum;
};

struct thread_data *thread;

void *PrintHello(void *threadarg)
{
	struct thread_data *my_data= (struct thread_data *) threadarg;
	
printf("Before:  my_data_task no %d, my_data_sum=%d\n",my_data->thread_id,my_data->sum);
	
  
    pthread_exit((void *)(my_data));
 
 }

int main(void)
{
	pthread_t threadone;
	thread= calloc (sizeof (struct thread_data), 1);
 int t=0;
  thread->thread_id = t;
  thread->sum = t*100;//initial sum
printf("TaskNo=%d  sum  = %d\n",thread->thread_id,thread->sum );
  printf("Creating thread %d\n", t);
  int rc = pthread_create(&threadone, NULL, PrintHello, thread);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  
sleep(2);
          printf("joining thread no. %d\n",t);
        pthread_join(threadone,(void **)&thread);
        
     //   free (thread_data_array[t]);
    
  pthread_exit(NULL);
printf("This is never printed");

}

/******************************************************************************************
Execute each case with the command 'time ./a.out' and fill the following columns. Observe the mapping or thread to processing unit. Analyse the different cases in terms of time taken.

	Case 1		Case 2a	Case 2b	Case 2c	Case 3
real
usr
sys

********************************************************************************************/
