/* Pipe is a mechanism for IPC between related processes ie parent and child */
/* It’s a unidirectional mechanism of IPC. You can send and receive data from source to destination, but not at a time. PIPE can be created using pipe() system call and it will return two file descriptors. The arguments to be passed to pipe() should be an array of integers.
int pipefd[2]; can be a valid sample here.
After the system call is executed it would return 2 fds one fd[0] and other fd[1].
fd[0] – Always should be kept as read end. fd[1] – Always should be write end. 
changing the above may result in unpredictable results.
More importantly, pipes have to be used with related processes.
They are un-named and the data that you pass will come out in the same order.
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(void)
{
	int ptocpipefd[2],ctoppipefd[2]; //this is to be passed to the pipe system call.
	//ptocpipefd is pipe from parent to child i.e; parent write and child read.
	//ctoppipefd is pipe from child to parent i.e; child write and parent read.
	pid_t ret;
	char buffer[15]; //this buffer is where the data is to be kept
	if(pipe(ptocpipefd)==-1)
	{
		fprintf(stderr,"pipe failed");
	} 
	if(pipe(ctoppipefd)==-1)
	{
		fprintf(stderr,"pipe failed");
	} 
	//pipe is formed. There will be two return values. One for read and the other for write. Linux treats pipe as a special type of a file. So read end is a file and write end is also a file.
	ret=fork();
	if(ret>0) //parent process
	{
		close(ptocpipefd[0]);//closing the unused end of the pipe i.e read end for parent process so that the process reading from the pipe i.e the child process can detect EOF(read()returns 0).
		fflush(stdin); //clean the std input line.
		printf("\n I am Parent \n");
		write(ptocpipefd[1], "Hello Friends.",15); //this is to write the contents into write end of the pipe i.e pipefd[1]. 15 means we are writing 15 characters to the buffer including ‘\0’
		close(ptocpipefd[1]);
		sleep(10); //parent is made to sleep till parent writes the contents.
		
		close(ctoppipefd[1]);//closing the write end of ctoppipe 
		fflush(stdin);
		
		read(ctoppipefd[0], buffer, sizeof(buffer));
		printf("Message recev in PARENT:\n");
		write(1,buffer,sizeof(buffer)); // 1 means the std output i.e monitor
		printf("\n");
		close(ctoppipefd[0]);
		
	}
//understand like parent has deposited some money and then child takes it.
	if(ret==0)
	{
		close(ptocpipefd[1]);//closing the unused end of pipe i.e write end for child process.
		sleep(5); //child is made to sleep till parent writes the contents.
		fflush(stdin);
		printf("\n I am CHILD. Message received is \n");
		//data already written at the write end can be read from here.
		
		read(ptocpipefd[0], buffer, sizeof(buffer));
		// the data is now read, but we need to display in the screen right. For that purpose we are keeping the data in buffer. From buffer we can write it to the display.
		puts(buffer);
		printf("\n");
		for(int i=0;buffer[i]!='\0';i++)
		 {	if(buffer[i]>='A' && buffer[i]<='Z')
		 		buffer[i]+=32;
		 	if(buffer[i]>='a' && buffer[i]<='z')
		 		buffer[i]-=32;
		}
		
		//write(1,buffer,sizeof(buffer)); // 1 means the std output i.e monitor
		close(ptocpipefd[0]);
		
		close(ctoppipefd[0]);//closing the readend of ctop pipe
		fflush(stdin); //clean the std input line.
		write(ctoppipefd[1], buffer,sizeof(buffer)); //this is to write the contents into write end of the ctoppipe.
		close(ctoppipefd[1]);
		
		
	}
return 0;
}
