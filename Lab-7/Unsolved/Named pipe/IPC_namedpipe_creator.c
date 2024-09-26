#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	int res1;
	res1=mkfifo("fifo1",0777);//creates a named pipe with the name fifo1;
	printf("named pipe created with res1=%d\n",res1);
	
return 0;
}
