/*pipe*/
#include<stdio.h>
#include<unistd.h>
#define MAXSIZE 20

int main()
{
	char *msg1 = "msg1";
	char *msg2 = "msg2";
	char *msg3 = "msg3";
	
	char inbuf[MAXSIZE];
	int p[2],i;
	
	write(p[1], msg1, MAXSIZE);
}
