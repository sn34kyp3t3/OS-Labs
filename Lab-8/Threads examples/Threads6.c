#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *printsquare(void *a)
{
int *n = (int *)a;
    
    (*n)*=(*n);
    

	printf("Square= %d\n",*n);
	pthread_exit(NULL);
}

int main()
{
	pthread_t T1;
	int x=20;
	
		pthread_create(&T1, NULL, printsquare,&x);
		pthread_join(T1,NULL);
	

	pthread_exit(NULL);
printf("In main: Square= %d\n",x);
return 0;
}

