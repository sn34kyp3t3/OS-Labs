# to find the sum of first n numbers. Read n from command line.

#include < pthread.h >
#include < stdio.h >

int sum;

void *runner ( void *param );

int main ( int argc, char *argv[ ] ){
pthread_t tid;
pthread_attr_t attr;
pthread_attr_init ( &attr);
pthread_create ( &tid, &attr, runner, argv [ 1 ] );
pthread_join ( tid, NULL );
printf( “ sum = %d \n”, sum);
}
// runner function
void *runner ( void *param ){
int upper = atoi (param);
int i; sum=0;
if ( upper > 0 ) {
for ( i=1; i <= upper; i++ ){
sum = sum + i;
}
}
pthread_exit ( 0 );
}

