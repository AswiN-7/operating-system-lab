/*
	get input  by command line aruments 
	it's function in grep
	search for given input(argv[1]) and print the entire line
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
# include<unistd.h>
#include<dirent.h>
#include<libgen.h>
extern int errno;
void search(char line[],char str[]);

int main(int argc, char*argv[])
{
	DIR *dir;
	struct dirent *dp;
	char c[1000];
	int sz;
		
	char file [100], search_op[100];
	if(argv[1]==NULL)
	{
		printf("enter key word to search\n");
		exit(0);
	}
	
	if(argv[2]==NULL)
	{
		printf("enter souce file\n");
		exit(0);
	}
	strcpy(search_op,argv[1]);
	strcpy(file,argv[2]);
	
	
	int fd1=open(file, O_RDONLY);
	if(fd1==-1)
	{
		printf("can't open file");
		perror("");
		exit(0);
	}
	int size_of_sop=strlen(search_op);
	sz = read(fd1, c, 1000);
	c[sz]='\0';
	printf("------------\n");		//printing file contents
	printf("%s",c);
	printf("-----------\n");
	search(c, search_op);	//searching function c->input file contents, 	search_op->key str
		
}
void search(char line[],char str[])
{
	int i, j, k, count, len, len1, l, newline=-1,line_no=1;
	len1=strlen(str);
	len=strlen(line);
	
	for(i=0;i<len+1;i++)
	{
		j=i;
		count=0;
		while(line[j]!=' '&&line[j]!='\0'&&line[j]!='\n')
		{
			++count;
			++j;
		}

		if(len1==count)
		{
			for(k=0;k<len1;k++)
			{
				if(str[k]!=line[i+k])
				break;
				else if(k+1==len1)
				{
					l=newline+1;
					printf("%d) ",line_no);
					while(line[l]!='\n' && line[l]!='\0')	//printing matching lines
					{
						if(l==i)			//high lighter
							printf("[");
							
						printf("%c",line[l++]);
						
						if(i+len1==l)		//high lighter
							printf("]");
					}
					printf("\n");	
				}
			}
		}
		if(line[j]=='\n')			//to identify new line 
		{
			newline=j;
			line_no++;
		}
		i+=count;
	} 
	   
}
/*
SAMPLE  I/O

an@aswin:~/Desktop/sem4/os_labexp/ex2$ ./3 new inp.txt 
------------
this is new file new
yes is new 2
kk bye 
-----------
1) this is [new] file new
1) this is new file [new]
2) yes is [new] 2
*/
