#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main()
{
	int res,n;
	res=open("fifo1",O_WRONLY);
	write(res,"Good Day from India",100);
	printf("Sender process %d sent the data\n",getpid());
	close(res);	
return 0;
}
