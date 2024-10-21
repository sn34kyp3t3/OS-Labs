/******************************************************************************
  A "hello world" Pthreads program to experiment on core affinity and analyze the time taken in 6 different cases.
******************************************************************************/
/* compile with -lpthread and execute eg: ./a.out 2

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h> //for set_affinity
#include <pthread.h> //for pthread_setaffinity_np
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>// for get_nprocs()
#define NUM_THREADS	8
#define totcases	5
#define SUBGROUP_CNT 5
int subtotal[NUM_THREADS];
int caseno,totpus;//totpus is total processing units
struct student_data
{
   int student_id;
   int quiz;
   int attd;
   int assignment;
   int midsem;
   int compre;
   int sum;
};

struct student_data *student_data_array[NUM_THREADS];
int a[NUM_THREADS][SUBGROUP_CNT+2]={{0,12,8,10,30,40,0},{1,10,7,10,25,35,0},{2,9,6,9,24,25,0},{3,8,5,10,20,15,0},{4,5,5,9,15,10,0},{5,6,4,10,18,15,0},{6,7,6,9,10,24,0}, {7,8,7,8,22,26,0}};

void *Computesum(void *threadarg)
{
   int s_id;
   int s_quiz;
   int s_attd;
   int s_assignment;
   int s_midsem;
   int s_compre;
   int s_sum;
   
	cpu_set_t cpuset;
	pthread_t TID;
	pid_t tid;
	struct student_data *my_data;
	my_data = calloc (sizeof (struct student_data), 1);
	my_data = (struct student_data *) threadarg;
 s_id=my_data->student_id;
 s_quiz=my_data->quiz;
 s_attd=my_data->attd;
 s_assignment=my_data->assignment;
 s_midsem=my_data->midsem;
 s_compre=my_data->compre;
 s_sum=my_data->sum;
 
   switch(caseno)
   {
 
//   Case 1: on Multiprocessor system with migration
    
     case 1: 
	
	sleep(1);

	TID=pthread_self();
	pthread_setaffinity_np(TID, sizeof(cpu_set_t), &cpuset);
	pthread_getaffinity_np(TID, sizeof(cpu_set_t), &cpuset);

	my_data->sum+=my_data->quiz;
	my_data->sum+=my_data->attd;
	my_data->sum+=my_data->assignment;
	my_data->sum+=my_data->midsem;
	my_data->sum+=my_data->compre;
		
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on PU %d with sum = %d\n", s_id, j,my_data->sum);
		
 
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
		
	CPU_ZERO(&cpuset);	
	CPU_SET(s_id%totpus,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	my_data->sum+=my_data->quiz;
	my_data->sum+=my_data->attd;
	my_data->sum+=my_data->assignment;
	my_data->sum+=my_data->midsem;
	my_data->sum+=my_data->compre;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on PU %d with sum = %d\n", s_id, j,my_data->sum);

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
	
	CPU_ZERO(&cpuset);	
	CPU_SET(s_id%totpus/2,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	my_data->sum+=my_data->quiz;
	my_data->sum+=my_data->attd;
	my_data->sum+=my_data->assignment;
	my_data->sum+=my_data->midsem;
	my_data->sum+=my_data->compre;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on PU %d with sum = %d\n", s_id, j,my_data->sum);
		
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
	
	CPU_ZERO(&cpuset);	
	if(s_id%2!=0) CPU_SET((s_id%(totpus/2))+1,&cpuset);
	else CPU_SET((s_id%(totpus/2)),&cpuset);

	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	my_data->sum+=my_data->quiz;
	my_data->sum+=my_data->attd;
	my_data->sum+=my_data->assignment;
	my_data->sum+=my_data->midsem;
	my_data->sum+=my_data->compre;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on PU %d with sum = %d\n", s_id, j,my_data->sum);
		
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
	
	CPU_ZERO(&cpuset);	
	CPU_SET(s_id%s_id,&cpuset);
	
	tid=gettid();
	sched_setaffinity(tid,sizeof(cpu_set_t), &cpuset);
	
	my_data->sum+=my_data->quiz;
	my_data->sum+=my_data->attd;
	my_data->sum+=my_data->assignment;
	my_data->sum+=my_data->midsem;
	my_data->sum+=my_data->compre;
	
	for (int j = 0; j < CPU_SETSIZE; j++)
	if (CPU_ISSET(j, &cpuset))
	printf("TaskNo=%d is running on PU %d with sum = %d\n", s_id, j,my_data->sum);
	
    break;
    default: printf("control never comes here\n");
    }                
  
    pthread_exit((void *)(my_data));
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int *taskids[NUM_THREADS];
int rc, t, sum;
caseno=atoi(argv[1]);
if(caseno<1 || caseno>5)
{ printf("enter case no betn 1 and 5\n");
return 0;
}
totpus=get_nprocs();//totpus means total processing units
printf("total processing units=%d\n",totpus);
sum=0;


	for(t=0;t<NUM_THREADS;t++) {
	 student_data_array[t] = calloc (sizeof (struct student_data), 1);
	 int x=0;
	 student_data_array[t]->student_id=a[t][x];
	 student_data_array[t]->quiz=a[t][++x];
	 student_data_array[t]->attd=a[t][++x];
	 student_data_array[t]->assignment=a[t][++x];
	 student_data_array[t]->midsem=a[t][++x];
	 student_data_array[t]->compre=a[t][++x];
	 student_data_array[t]->sum=a[t][++x];
 
  // printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, Computesum, student_data_array[t]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
  
sleep(5);
  for(t=0;t<NUM_THREADS;t++)
    {
      //  printf("joining thread no. %d\n",t);
        pthread_join(threads[t],(void **)&student_data_array[t]);
        subtotal[t]=student_data_array[t]->sum;
        free (student_data_array[t]);
    }
     long double finalsum=0;
     for(t=0;t<NUM_THREADS;t++)
    {
       // printf("student[%d]=%d\n",t,subtotal[t]);
        finalsum+=subtotal[t];
    }            
  //printf("Final sum= %Lf\n",finalsum);
  printf("Average= %Lf\n",finalsum/NUM_THREADS);
  
  printf("time taken by case %d\n",caseno);
pthread_exit(NULL);
printf("This is never printed");

}

/******************************************************************************************
Execute each case with the command 'time ./a.out' and fill the following columns. Observe the mapping of thread to processing unit. Analyse the different cases in terms of time taken.

	Case1	Case2	Case3	Case4	Case5	
real
usr
sys

********************************************************************************************/
