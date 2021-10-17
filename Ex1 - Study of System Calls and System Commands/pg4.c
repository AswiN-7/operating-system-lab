/*exit wait */
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	
	pid_t process;
	process=fork();
	if(process==0)
	{
		printf("in child process\n");
		sleep(3);
		printf("after sleep for 3 seconds in child\n");
	}
	else if (process>0)
	{
	    printf("in parent process before wait\n");
		wait(NULL);
		printf("after wait in parent\n");
	}
	printf("before exit \n");
	exit(EXIT_SUCCESS);
	printf("afte exit \n");	
}
/*
185001027@OSNPL-C27:~/Desktop/os lab/ex1$ ./4
in parent process before wait
in child process
after sleep for 3 seconds in child
after wait in parent
before exit
*/

