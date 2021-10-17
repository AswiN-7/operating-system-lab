/*create open close*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include <fcntl.h>  

int main()
{
	int create_p;
	create_p=creat("newfile.txt",777);
	printf("file created %d\n",create_p);
	int open_p;
	open_p=open("newfile.txt",O_RDONLY);
	printf("open process %d\n",open_p);
	
	printf("closing file %d\n",close(open_p));
	
}
