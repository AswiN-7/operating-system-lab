/*
	cp command
	argv[1]->option(-i)
	argv[2]-> source
	argv[3]->destination
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
# include<unistd.h>
extern int errno;
int main(int argc, char*argv[])
{
	int fd1= open(argv[2],O_RDONLY);
	printf("fd =%d\n",fd1);
	
	if(fd1==-1)
	{
		printf("error number %d\n",errno);
		perror("program");
	}
	else
	printf("file opened\n");
	
	char *c = (char*) calloc(1000,sizeof(char)); 
	int sz= read(fd1, c, 1000);
	c[sz]='\0';
	printf("source file contents: \n%s\n", c);
	
	int fd2 = open(argv[3], O_WRONLY);
	if(fd2==-1)
	{
		printf("writing file is not opened\n");
		perror("program");
	}
	else
	{	
		if(strcmp(argv[1],"-i")==0)
		{
			printf("do you want to overwritte the file %s\n",argv[3]);
			char cc;
				scanf("%c",&cc);
			if(cc=='y')
			{
				write(fd2,c,sz);
				printf("\ncontents written\n");
			}
		}
		else
		{
			write(fd2,c,sz);
			printf("\ncontents written\n");
		}
		
	}
	
	int clw=close(fd2);
	if(clw<0)
	{
		printf("write file is closed correctly\n ");
	}
	int cl= close(fd1);
	if(cl<0)
		printf("file does not closed properly\n");
	else
	printf("file closed\n");
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex2$ gcc ex2-1.c -ocp
an@aswin:~/Desktop/sem4/os_labexp/ex2$ ./cp 0 inp.txt temp.txt 
fd =3
file opened
source file contents: 
this is new file new
yes is new 2
kk bye 


contents written
file closed
an@aswin:~/Desktop/sem4/os_labexp/ex2$ ./cp -i inp.txt temp.txt 
fd =3
file opened
source file contents: 
this is new file new
yes is new 2
kk bye 

do you want to overwritte the file temp.txt
y

contents written
file closed
*/
