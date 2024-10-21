/******************************************************************************
  A "hello world" Pthreads program to experiment on core affinity and analyze the time taken in 6 different cases.
******************************************************************************/
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h> //for set_affinity
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/sysinfo.h>// for get_nprocs()
#define NUM_THREADS	8
#define totcases	6
#define SUBGROUP_CNT 10
int subtotal[NUM_THREADS];//totpus is total processing units
int caseno,totpus;
struct thread_data
{
   int	thread_id,sum;
};

struct thread_data *thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
	int taskid,sum,next_num;
	cpu_set_t cpuset;
	pthread_t TID;
	pid_t tid;
	struct thread_data *my_data;
	my_data = calloc (sizeof (struct thread_data), 1);
 
   switch(caseno)
   {
 
//   Case 1: on Multiprocessor system with migration
    
     case 1: 
	
	sleep(1);

	TID=pthread_self();
	pthread_setaffinity_np(TID, sizeof(cpu_set_t), &cpuset);
	pthread_getaffinity_np(TID, sizeof(cpu_set_t), &cpuset);

	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
	sum=my_data->sum;

	next_num=sum;
	for(int j=1;j<SUBGROUP_CNT;j++)
	{
		sum+=++next_num;
	}		
	my_data->sum=sum;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on CPU %d with sum of %d to %d = %d\n", taskid, j,taskid*SUBGROUP_CNT,taskid*SUBGROUP_CNT+SUBGROUP_CNT-1,sum);
		
 
/*  Case 2: without migration 
 
Processing		Core Id	Task set
unit No.
0			0		{0,4}
1			1		{1,5}
2			0		{2,6}
3			1		{3,7}
*/
  break;
  case 2: 
	sleep(1);
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
        sum=my_data->sum;
	
	CPU_ZERO(&cpuset);	
	CPU_SET(taskid%totpus,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	next_num=sum;
	for(int j=1;j<SUBGROUP_CNT;j++)
	{
		sum+=++next_num;
	}		
	my_data->sum=sum;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on CPU %d with sum of %d to %d = %d\n", taskid, j,taskid*SUBGROUP_CNT,taskid*SUBGROUP_CNT+SUBGROUP_CNT-1,sum);
		
	
	
/*
  Case 3: without migration on same core ids

Processing		Core Id	Task set
unit No.
0			0		{0,2,4,6}
1			1		{1,3,5,7}
2			0		{NULL}
3			1		{NULL}
*/
    break;
    case 3: 
	sleep(1);
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
        sum=my_data->sum;
	
	CPU_ZERO(&cpuset);	
	CPU_SET(taskid%totpus/2,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	next_num=sum;
	for(int j=1;j<SUBGROUP_CNT;j++)
	{
		sum+=++next_num;
	}		
	my_data->sum=sum;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on CPU %d with sum of %d to %d = %d\n", taskid, j,taskid*SUBGROUP_CNT,taskid*SUBGROUP_CNT+SUBGROUP_CNT-1,sum);
		
	

/*
  Case 4: without migration on same core ids
Processing		Core Id	Task set
unit No.
0			0		{0,2,4,6}
1			1		{NULL}
2			0		{1,3,5,7}
3			1		{NULL}
*/
  break;
  case 4:

	sleep(1);
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
        sum=my_data->sum;
	
	CPU_ZERO(&cpuset);	
	if(taskid%2!=0) CPU_SET((taskid%(totpus/2))+1,&cpuset);
	else CPU_SET((taskid%(totpus/2)),&cpuset);

	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	next_num=sum;
	for(int j=1;j<SUBGROUP_CNT;j++)
	{
		sum+=++next_num;
	}		
	my_data->sum=sum;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on CPU %d with sum of %d to %d = %d\n", taskid, j,taskid*SUBGROUP_CNT,taskid*SUBGROUP_CNT+SUBGROUP_CNT-1,sum);
		
/*
  Case 5: on uniprocessor system
Processing		Core Id	Task set
unit No.
0			0		{0,1,2,3,4,5,6,7,8}
1			1		{NULL}
2			0		{NULL}
3			1		{NULL}
*/
   break;
   case 5:
	
	sleep(1);
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
        sum=my_data->sum;
	
	CPU_ZERO(&cpuset);	
	CPU_SET(taskid%taskid,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	next_num=sum;
	for(int j=1;j<SUBGROUP_CNT;j++)
	{
		sum+=++next_num;
	}		
	my_data->sum=sum;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on CPU %d with sum of %d to %d = %d\n", taskid, j,taskid*SUBGROUP_CNT,taskid*SUBGROUP_CNT+SUBGROUP_CNT-1,sum);
		
		
	                
 /*  Case 6: without migration using processes
 
Processing		Core Id	Process set
unit No.
0			0		{0,4}
1			1		{1,5}
2			0		{2,6}
3			1		{3,7}
*/
     break;              
    default: printf("enter number between 1 and %d\n",totcases);
    }               
	 
  
    pthread_exit((void *)(my_data));
 
 }

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int *taskids[NUM_THREADS];
int rc, t, sum;
caseno=atoi(argv[1]);
totpus=get_nprocs();//totpus means total processing units
printf("total processing units=%d\n",totpus);
sum=0;


for(t=0;t<NUM_THREADS;t++) {
 thread_data_array[t] = calloc (sizeof (struct thread_data), 1);
 
  thread_data_array[t]->thread_id = t;
  thread_data_array[t]->sum = t*SUBGROUP_CNT;//initial sum
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, thread_data_array[t]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
sleep(5);
  for(t=0;t<NUM_THREADS;t++)
    {
        printf("joining thread no. %d\n",t);
        pthread_join(threads[t],(void **)&thread_data_array[t]);
        subtotal[t]=thread_data_array[t]->sum;
        free (thread_data_array[t]);
    }
     int finalsum=0;
     for(t=0;t<NUM_THREADS;t++)
    {
        printf("subtotal[%d]=%d\n",t,subtotal[t]);
        finalsum+=subtotal[t];
    }            
  
  printf("FINAL SUM from 0 to %d = %d\n",SUBGROUP_CNT*NUM_THREADS,finalsum);
  
  printf("time taken by case %d\n",caseno);
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
