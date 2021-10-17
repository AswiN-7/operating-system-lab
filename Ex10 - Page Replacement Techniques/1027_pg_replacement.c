#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct node_page node_page;

struct node_page{
	char process[20];
	int count;
};

int search(node_page p[], int size, char key[]);
void display(node_page p[], int size);
int find_first(node_page p[], int size);
int find_optimal(node_page p[], char r_string[][20], int size, int r_size, int i);
																							//main
int main(void)
{
	int option, free_frames, required_frames;
	char r_string[CHAR_MAX][20];
	while(1)
	{
		printf("1 --read input\n2 --FIFO\n3 --OPTIMAL\n4 --LRU\n5 --LFU\n6 --exit\nenter your option : ");
		scanf("%d", &option);
		if(option==1)
		{	
			printf("Enter the number of free frames : ");
				scanf("%d", &free_frames);
			printf("Enter the number of frames required by the process : ");
				scanf("%d", &required_frames);
			printf("enter reference string :\n");
			for(int i=0;i<required_frames;i++)
			{
					scanf("%s", r_string[i]);
			}
		}
																											//FIFO
		else if(option==2)
		{
			printf("\t\tFIFO\n");
			int search_res, page_fault=0, first;
			node_page p [10]={};
			for(int i=0;i<required_frames;i++)
			{
				search_res=search(p, free_frames, r_string[i]);
				if(search_res==-1)
				{
					if(page_fault<free_frames)																		//checking wheather all frames are filled
					{
						strcpy(p[page_fault].process, r_string[i]);
						p[page_fault].count=i;
						page_fault++;
						display(p, free_frames);
					}
					else																								//all frames are filled and placing by fifo
					{	
						first=find_first(p, free_frames);
						strcpy(p[first].process, r_string[i]);
						p[first].count=i;
						page_fault++;
						display(p, free_frames);
					}
				}
			}
			printf("page fault : %d\n", page_fault);
		}
																														//OPTIMAL
		else if(option==3)
		{
			printf("\t\tOPTIMAL\n");
			 int search_res, page_fault=0, opt;
			node_page p [10]={};
			for(int i=0;i<required_frames;i++)
			{
				printf("%s %d\n", r_string[i], i);
				search_res=search(p, free_frames, r_string[i]);
				if(search_res==-1)
				{
					if(page_fault<free_frames)																		//checking wheather all frames are filled	
					{
						strcpy(p[page_fault].process, r_string[i]);
						page_fault++;
						display(p, free_frames);
					}
					else																							//all frames are filled and  by optimal
					{	
						opt=find_optimal(p,r_string, free_frames, required_frames, i);
						strcpy(p[opt].process, r_string[i]);
						page_fault++;
						display(p, free_frames);
					}
				}
			}
			printf("page fault : %d\n", page_fault);
		}
		else if(option==4)
		{
			printf("\t\tLRU\n");
			int search_res, page_fault=0, lru;
			node_page p [10]={ };
			for(int i=0;i<required_frames;i++)
			{
				search_res=search(p, free_frames, r_string[i]);
				if(search_res==-1)
				{
					if(page_fault<free_frames)															//checking wheather all frames are filled
					{
						strcpy(p[page_fault].process, r_string[i]);
						p[page_fault].count=i;
						page_fault++;
						display(p, free_frames);
					}
					else																					//all frames are filled and choosing a frame by lru
					{	
						lru=find_first(p, free_frames);
						strcpy(p[lru].process, r_string[i]);
						p[lru].count=i;
						page_fault++;
						display(p, free_frames);
					}
				}
				else
				{
					p[search_res].count=i;															//setting lru count
				}
			}
			printf("page fault : %d\n", page_fault);
		}
		else if(option==5)
		{
			printf("\t\tLFU\n");
			int search_res, page_fault=0, lfu;
			node_page p [10]={};
			for(int i=0;i<required_frames;i++)
			{
				search_res=search(p, free_frames, r_string[i]);
				if(search_res==-1)
				{
					if(page_fault<free_frames)
					{
						strcpy(p[page_fault].process, r_string[i]);
						p[page_fault].count=1;
						page_fault++;
						display(p, free_frames);
					}
					else
					{	
						lfu=find_first(p, free_frames);
						strcpy(p[lfu].process, r_string[i]);
						p[lfu].count=1;
						page_fault++;
						display(p, free_frames);
					}
				}
				else
				{
					p[search_res].count++;
				}
			}
			printf("page fault : %d\n", page_fault);
		}
		else if(option==6)
		{
			break;
		}
	}
	printf("program ended !\n"); 
}
int search(node_page p[], int size, char key[])
{
	for(int i=0;i<size;i++)
	{
		if(strcmp(p[i].process, key)==0)
			return i;
	}
	return -1;
}
void display(node_page p[], int size)
{
	printf("---------\n");
	for(int i=0;i<size;i++)
	{
		printf("| %s\t|\n", p[i].process);
		printf("---------\n");
	}
	printf("\n");
}

int find_first(node_page p[], int size)
{
	int first=p[0].count;
	int position=0;
	for(int i=1;i<size;i++)
	{
		if(first>p[i].count)
		{
			first=p[i].count;
			position=i;
		}
	}
	return position;																	//comparing all and selecting which has small count
}

int find_optimal(node_page p[], char r_string[][20], int size, int r_size, int i)
{	
	int count=0;
	int optimal[100];
	for(int k=0;k<size;k++)
	{
		optimal[k]=-1;
	}
	i+=1;
	while(count<size&&i<=r_size)
	{
		for(int j=0;j<size;j++)
		{
			if(strcmp(r_string[i],p[j].process)==0&&optimal[j]==-1)	//comparing all frames with r_string
			{
				optimal[j]=i;
				count++;
				break;
			}
		}
		i++;
	}
	int opt=optimal[0];
	int position=0;
	for(int k=0;k<size;k++)
	{
		if(optimal[k]!=-1)
		{
			if(opt<optimal[k])
			{
				opt=optimal[k];
				position=k;
			}
		}
		else
			return k;
	}
	return position;
}

/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex10$ gcc pg_replacement.c -op
an@aswin:~/Desktop/sem4/os_labexp/ex10$ ./p
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 1
Enter the number of free frames : 4
Enter the number of frames required by the process : 20
enter reference string :
7
0
1
2
0
3
0
4
2
3
0
3 
2
1
2
0
1
7
0

1
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 2
		FIFO
---------
| 7	|
---------
| 	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 4	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 4	|
---------
| 0	|
---------
| 2	|
---------

---------
| 3	|
---------
| 4	|
---------
| 0	|
---------
| 1	|
---------

---------
| 2	|
---------
| 4	|
---------
| 0	|
---------
| 1	|
---------

---------
| 2	|
---------
| 7	|
---------
| 0	|
---------
| 1	|
---------

page fault : 10
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 3
		OPTIMAL
7 0
---------
| 7	|
---------
| 	|
---------
| 	|
---------
| 	|
---------

0 1
---------
| 7	|
---------
| 0	|
---------
| 	|
---------
| 	|
---------

1 2
---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 	|
---------

2 3
---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

0 4
3 5
---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

0 6
4 7
---------
| 3	|
---------
| 0	|
---------
| 4	|
---------
| 2	|
---------

2 8
3 9
0 10
3 11
2 12
1 13
---------
| 3	|
---------
| 1	|
---------
| 4	|
---------
| 2	|
---------

2 14
0 15
---------
| 3	|
---------
| 0	|
---------
| 4	|
---------
| 2	|
---------

1 16
---------
| 3	|
---------
| 1	|
---------
| 4	|
---------
| 2	|
---------

7 17
---------
| 3	|
---------
| 7	|
---------
| 4	|
---------
| 2	|
---------

0 18
---------
| 0	|
---------
| 7	|
---------
| 4	|
---------
| 2	|
---------

1 19
---------
| 1	|
---------
| 7	|
---------
| 4	|
---------
| 2	|
---------

page fault : 12
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 4
		LRU
---------
| 7	|
---------
| 	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 4	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

page fault : 8
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 5
		LFU
---------
| 7	|
---------
| 	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 4	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 3	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

---------
| 7	|
---------
| 0	|
---------
| 1	|
---------
| 2	|
---------

page fault : 8
1 --read input
2 --FIFO
3 --OPTIMAL
4 --LRU
5 --LFU
6 --exit
enter your option : 6
program ended !
*/
