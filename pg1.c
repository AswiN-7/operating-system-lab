#include<stdio.h>
#include<sys/types.h>
int main()
{
	pid_t pidvalue;
	
	printf("welcome to os world\n");
	pidvalue=fork();
	if(pidvalue==0)
		printf("lets start learning(child)\n");
	else if(pidvalue>0)
		printf("lets start learning(parent)\n");
	else
		printf("process is failed\n");
}
/*
welcome to os world
lets start learning(parent)
lets start learning(child)
*/
