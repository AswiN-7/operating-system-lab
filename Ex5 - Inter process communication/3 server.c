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
int main()
{
	int pid;
	char *a,*b,c;
	int id,n,i,wid,wv;
	id=shmget(111,50,IPC_CREAT | 00666);
	wid=shmget(112,2,IPC_CREAT |00666);
	b=shmat(wid, NULL, 0);
	a=shmat(id,NULL,0);
	printf("server\n");
	while(1)
	{	
		printf("enter msg here : ");
			scanf("%s",a);
		b[0]='y';
		while(b[0]=='y');	
		if(strcmp(a, "-1")==0)
		{
			b[0]='y';
			break;
		}
		
		printf("%s\n", a);
		
	}
	shmdt(a);
	shmdt(b);	
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ gcc server.c -os
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ ./s
server
enter msg here : hi
hello
enter msg here : do_you_any_prob._in_system
no!_everything_is_good
enter msg here : alright!
mm..
enter msg here : okay..bye!!
thanks!!
enter msg here : -1
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ 

*/
