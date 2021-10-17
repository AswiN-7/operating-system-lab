/*
	ls command 
	options
		(empty) no options 
		-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<libgen.h>


int main(int argc, char*argv[])
{
	DIR *dir;
	struct dirent *dp;
	
	if((dir = opendir(".")) == NULL)
	{
		perror("cannot open ");
		exit(1);
	}
	if(argv[1]== NULL)
	{
		while((dp = readdir(dir)) != NULL)
		{
			if(strcmp(dp->d_name, ".")!=0 && strcmp(dp->d_name, "..")!=0)
			{
				printf("%s\t\t", dp->d_name);	
			}
		}
		printf("\n");
	}
	else if(strcmp(argv[1], "-1")==0)
	{
		while((dp = readdir(dir)) != NULL)
		{
			if(strcmp(dp->d_name, ".")!=0 && strcmp(dp->d_name, "..")!=0)
			{
				printf("%s\n", dp->d_name);	
			}
		
		}
	}
	else if(strcmp(argv[1], "-R")==0)
	{
		
	}
	closedir(dir);
}

/*
SAMPLE I/O

an@aswin:~/Desktop/sem4/os_labexp/ex2$ gcc ex2-2.c -o2
an@aswin:~/Desktop/sem4/os_labexp/ex2$ ./2
replacestr.c		3		2		b2_f-ex2-3.c		ex2-11.c		1inp.txt		ex2-2.c		b1-ex2-3.c		ex2-3.c		2-ex2-cmds.pdf		ex2-1.c		
an@aswin:~/Desktop/sem4/os_labexp/ex2$ ./2 -1
replacestr.c
3
2
b2_f-ex2-3.c
ex2-11.c
1
inp.txt
ex2-2.c
b1-ex2-3.c
ex2-3.c
2-ex2-cmds.pdf
ex2-1.c

	
*/
