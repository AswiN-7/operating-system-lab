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
	char *a,*b, *chart_c;
	int i, id, wid;
	printf("client\n");	
	id=shmget(111,50,0);
	wid=shmget(112,2,0);
	a=shmat(wid, NULL, 0);	
	b=shmat(id,NULL,0);
	a[0]='n';
	while(1)
	{
		while(a[0]=='n');
		if(strcmp(b,"-1")==0)
		{
			a[0]='n';
			//strcpy(a,b);
			break;
		}
		
		printf("%s\n",b);
		
		printf("enter msg here : ");
			scanf("%s", b);
		a[0]='n';
		
	}
	shmdt(a);	
	shmdt(b);
	shmctl(id, IPC_RMID,NULL);
	shmctl(wid, IPC_RMID, NULL);
}
/*
SAMPLE  I/O
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ gcc client.c -oc
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ ./c
client
hi
enter msg here : hello
do_you_any_prob._in_system
enter msg here : no!_everything_is_good
alright!
enter msg here : mm..
okay..bye!!
enter msg here : thanks!!
an@aswin:~/Desktop/sem4/os_labexp/ex5/chat$ 
*/
