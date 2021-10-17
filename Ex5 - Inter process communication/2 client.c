/*			order of execution => fisrt server than client
			-1 to end process(program)
*/

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
	id=shmget(111,100,0);
	wid=shmget(112,2,0);
	a=shmat(wid, NULL, 0);	
	b=shmat(id,NULL,0);
	while(1)
	{
		printf("file name : ");
			scanf("%s", b);
		a[0]='n';
		while(a[0]=='n');
		if(strcmp(b,"-1")==0)
		{
			a[0]='n';
			break;
		}
		
		printf("%s",b);
		
			
		
		
	}
	shmdt(a);	
	shmdt(b);
	shmctl(id, IPC_RMID,NULL);
	shmctl(wid, IPC_RMID, NULL);
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex5/file_contents_transfer$ gcc client.c -oc
an@aswin:~/Desktop/sem4/os_labexp/ex5/file_contents_transfer$ ./c
client
file name : new.txt 
this is a new file
used to visualize ipc
and display the contents to client from server
file name : -1
*/
