/*			fisrt server than client
			-1 to end process
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
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
	int pid;
	char *a,*b,*c,*temp;
	int id,n,i,wid,wv;
	id=shmget(111,100,IPC_CREAT | 00666);
	wid=shmget(112,2,IPC_CREAT |00666);
	b=shmat(wid, NULL, 0);
	a=shmat(id,NULL,0);
	printf("server\n");
	b[0]='y';
	while(1)
	{	
		
		printf("hi! enter file name \n ");
		while(b[0]=='y');	
		if(strcmp(a, "-1")==0)
		{
			b[0]='y';
			break;
		}
		
		printf("%s\n", a);
		strcpy(temp,a);
		//file op
		int  fd=open(temp,O_RDONLY);
		if(fd==-1)
		{
			strcpy(a,"file is not present");
		}
		else
		{
			c = (char*) calloc(1000,sizeof(char)); 
			int sz=read(fd, c,1000);
			c[sz]='\0';
			strcpy(a,c);
		}
		b[0]='y';
		
	}
	shmdt(a);
	shmdt(b);
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex5/file_contents_transfer$ gcc server.c -os
an@aswin:~/Desktop/sem4/os_labexp/ex5/file_contents_transfer$ ./s
server
hi! enter file name 
 new.txt
hi! enter file name 
*/
