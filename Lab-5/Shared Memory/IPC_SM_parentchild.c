#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/types.h>
#include<wait.h>
#define SIZE 5
int nums[SIZE]={1,2,3,4,5};

int main(void)
{
	int i;
	int *shared_memory;
	int shmid=shmget((key_t)2345,1024,0666|IPC_CREAT); //[1] parent creates SM
	printf("PARENT: id of shared memory is %d\n",shmid);
	
	shared_memory=shmat(shmid,NULL,0);//[1]//parent gets attached to the SM
	printf("Parent process attached at %p\n",shared_memory);	
	
	pid_t ret;
	ret=fork();//[1]
	if(ret==0) //child process
	{
		printf("\n I am child \n");
		int shmid=shmget((key_t)2345,1024,0666); //[1] child uses same key
		printf("CHILD: id of shared memory is %d\n",shmid);
	
		shared_memory=shmat(shmid,NULL,0);
		printf("Child process attached at %p\n",shared_memory);
		for(int i=0;i<SIZE;i++,shared_memory++)
		{
			*shared_memory = (nums[i]*2);//[1] child accesses copy of global array nums
			printf("CHILD: Data wrote to shared memory is : %d\n", *shared_memory);
		}
		exit(0);
	}
	
		printf("\n I am PARENT \n");
		wait(NULL);//[1] parent waiting for child to finish
		for(int i=0;i<SIZE;i++,shared_memory++)
			printf("Parent: Data read from shared memory is : %d\n", *shared_memory);//[1] printing in parent process and not in child.
	
	
	i=shmdt((int*)shared_memory);//[1]detached by parent process
return 0;
}
