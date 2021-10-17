/*wait sleep execl getpid getppid */
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int data;
	printf("enter data : ");
	scanf("%d",&data);	
	pid_t pidvalue;
	sleep(3);
	printf("welcome to os world\n");
	pidvalue=fork();
	if(pidvalue==0)
	{
		printf("befors sleep \n");
		sleep(3);
		printf("after sleep\n");

		execl("/bin/ls","/bin/ls",0);
		
		printf("lets start learning(child)\n");
		printf("%d\n",data);
		printf("child pid %d\n",getpid());
		
		printf("child ppid %d\n",getppid());
	}
	else if(pidvalue>0)
	{
		printf("lets start learning(parent)\n");
		printf("parent pid %d\n",getpid());
		printf("parent ppid %d\n",getppid());
		wait(NULL);
		printf("after wait in parent \n");
	}	
	else
		printf("process is failed\n");
}
/*
185001027@admins-32:~/Desktop$ ./2
enter data : 44
welcome to os world
lets start learning(parent)
pid 20119
ppid 19645
lets start learning(child)
44
pid 20120
ppid 16373

*/