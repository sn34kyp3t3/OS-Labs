#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define  NUM_THREADS 5

void *printsquare(void *a)
{
	printf("Square= %d\n",(long int) a*(long int) a);
	pthread_exit(NULL);
}
void *printcube(void *a)
{
	printf("Cube= %d\n",(long int) a*(long int) a*(long int) a);
	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	long x=20;
	int y=3;
	char z=10;
		printf("In main: creating thread %d\n",t);
		pthread_create(threads + t++, NULL, printsquare,(void*)x);
		pthread_create(threads + t++, NULL, printsquare,(void*)y);
		pthread_create(threads + t++, NULL, printsquare,(void*)z);


		pthread_create(threads + t++, NULL, printcube,(void*)x);
		pthread_create(threads + t++, NULL, printcube,(void*)y);
		

	for(t=0;t<NUM_THREADS;t++)
	{
		printf("joining thread#%d\n",t);
		pthread_join(threads[t],NULL);
	}

	pthread_exit(NULL);
}

