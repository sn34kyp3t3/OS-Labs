#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/types.h>
#include<wait.h>

int main(int argc, char* argv[])
{
	if(atoi(argv[1])<0) 
	{printf("only positive number please\n");
	exit(0);
	}
	if(argc>2) 
	{printf("only one number please\n");
	exit(0);
	}

	int i;
	int *shared_memory;
	int shmid;
	shmid=shmget((key_t)2345,1024,0666|IPC_CREAT);
	printf("PARENT: id of shared memory is %d\n",shmid);
	
	shared_memory=shmat(shmid,NULL,0);
	printf("Parent process attached at %p\n",shared_memory);	
	
	pid_t ret;
	ret=fork();
	if(ret==0) //child process
	{
		printf("\n I am child \n");
		shmid=shmget((key_t)2345,1024,0666);
		printf("CHILD: id of shared memory is %d\n",shmid);
	
		shared_memory=shmat(shmid,NULL,0);
		printf("Child process attached at %p\n",shared_memory);
		*shared_memory=atoi(argv[1]);
		for(int i=0;*shared_memory!=1;i++)
		{
			if(*shared_memory%2==0)
			{
				int i=*shared_memory;
				shared_memory++; 
				*shared_memory=i/2;
			}
			else
			{
				int i=*shared_memory;
				shared_memory++;
				*shared_memory=i*3+1;
			}
		}
		exit(0);
	}
		printf("\n I am PARENT \n");
		wait(NULL);
		for(int i=0;*shared_memory!=1;i++,shared_memory++)
			printf("Parent: Data read from shared memory is : %d\n", *shared_memory);
	
	i=shmdt((int*)shared_memory);
return 0;
}
