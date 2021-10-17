#include <sys/ipc.h>
# define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
#include<ctype.h>
// parent writing a char in shared memory and child reads it and prints it.
int main()
{
	int pid;
	char *a,*b,c;
	int id,n,i;
// you can create a shared memory between parent and child here or you can //create inside them separately.
	id=shmget(111,50,IPC_CREAT | 00666);
	pid=fork();
	if(pid>0) //parent
	{
		// id=shmget(111,50,IPC_CREAT | 00666);
		printf("parent\n");
		a=shmat(id,NULL,0);
		printf("enter text :");
			scanf("%s",a);
		wait(NULL);
		shmdt(a);
	}	
	else //child
	{
		sleep(3);
		//id=shmget(111,50,0);
		printf("child\n");
		b=shmat(id,NULL,0);
		//printf("\n child %c\n",b[0]);
		i=0;	
		while(b[i]!='\0')
		{
			printf("%c",toupper(b[i++]));
		}
		printf("\n");	
		shmdt(b);
	}
	shmctl(id, IPC_RMID,NULL);
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex5$ ./t
parent
enter text :oslab
child
OSLAB
*/
