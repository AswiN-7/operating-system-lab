#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define MAX_I 20

typedef struct node_frame node_frame;
typedef struct node_page node_page;
typedef struct node_process node_process;
typedef struct free_frame free_frame;

struct node_page{
	int f_no;
	node_frame *alloted_frame;
};

struct node_process{
    char process[20];
    int size;
    node_page  page[MAX_I];
    node_process* next;    
};

struct node_frame{
    int st_add;
    int alloted;
    struct node_process *p;
    struct node_frame *next;
};

struct free_frame
{	
	node_frame* frame;
	free_frame* next;
};
																							//main functions
node_frame* create_frames(node_frame* head, int phy_mem, int frame_size);
node_process* create_process();
node_process* remove_process(node_process* head, char p[],int frame_size, free_frame *head_ff);
free_frame* create_free_frame();
free_frame* append_free_frame(free_frame* head, free_frame* new);
free_frame* remove_alloted_frame(free_frame* head);
																							//Display functions
void display_frame(node_frame* head);
void display_free_frame(free_frame* head);
void display_page(node_process* p, int frame_size);
void display_process(node_process *head);

node_frame* create_frames(node_frame* head, int phy_mem, int frame_size)
{
	int partition=phy_mem/frame_size;
	int bytes=1024;
	node_frame* itr;
	for(int i=0;i<partition;i++)
	{
		node_frame* new=(node_frame*) malloc(sizeof(node_frame));
		new->st_add=i*frame_size*bytes;
		new->alloted=0;
		new->next=NULL;
		new->p=NULL;
		if(i==0)
		{
			head=new;
			itr=head;
		}
		else
		{
			itr->next=new;
			itr=new;
		}
	}
	return head;		
}

node_process* create_process()
{
	node_process* new=(node_process*)malloc(sizeof(node_process));
	printf("enter process id size : ");
		scanf("%s %d", new->process, &new->size);
	new->next=NULL;
	return new;
}

node_process* remove_process(node_process* head, char p[],int frame_size, free_frame *head_ff)
{
	node_process* itr;
	free_frame *new;
	int found=0;
	itr=head;
	if(head==NULL)
		printf("there is no process\n");
	else if(strcmp(head->process,p)==0)
	{
		for(int i=0;i<head->size/frame_size;i++)
		{
			head->page[i].alloted_frame->alloted=0;
			new=(free_frame*)malloc(sizeof(free_frame));
			new->frame=head->page[i].alloted_frame;
			head_ff=append_free_frame(head_ff, new);
		}
		if(head->next==NULL)
			head=NULL;	
		else
			head=head->next;	
	}
	else if(head->next!=NULL)
	{
		while(itr->next!=NULL)
		{
			if(strcmp(itr->next->process,p)==0)
			{
				found=1;
				for(int i=0;i<itr->next->size/frame_size;i++)
				{
					itr->next->page[i].alloted_frame->alloted=0;
					new=(free_frame*)malloc(sizeof(free_frame));
					new->frame=itr->next->page[i].alloted_frame;
					head_ff=append_free_frame(head_ff, new);
				}
				if(itr->next->next!=NULL)
					itr->next=itr->next->next;
				else
					itr->next=NULL;
					break;
				
			}
			itr=itr->next;
		}
		if(found==0)
			printf("no such process id found\n");			
	}
	else
	{	
		printf("no such process id found\n");
	}
	return head;
}

free_frame* create_free_frame()
{
	free_frame* new=(free_frame*)malloc(sizeof(free_frame));
	new->next=NULL;
	return new;
}

free_frame* append_free_frame(free_frame* head, free_frame* new)
{
	free_frame* itr;
	itr=head;
	while(itr->next!=NULL)
		itr=itr->next;
	itr->next=new;
	return head;
}

free_frame* remove_alloted_frame(free_frame* head)
{
	free_frame* itr;
	itr=head;
	if(head->next!=NULL)
		head=head->next;
	else
		head=NULL;
	return head;
} 

void display_process(node_process *head)
{
	printf("Display ProCess\n");
	node_process* itr;
	itr=head;
	if(itr==NULL)
		printf("no process \n");
	else
	while(itr!=NULL)
	{
		printf("%s %d\n", itr->process, itr->size);
		itr=itr->next;
	}
}

void display_free_frame(free_frame* head)
{
	printf("Displaying free frames\n");
	free_frame* itr;
	itr=head;
	while(itr!=NULL)
	{
		printf("-------- ");
		itr=itr->next;
	}
	printf("\n");
	itr=head;
	while(itr!=NULL)
	{
		printf("|%d\t", itr->frame->st_add);
		itr=itr->next;
	}
	printf("|\n");
	itr=head;
	while(itr!=NULL)
	{
		printf("-------- ");
		itr=itr->next;
	}
	printf("\n");
}

void display_page(node_process* p, int frame_size)
{	
	printf("page table of process %s\n", p->process);
	printf(" ---------------\n");
	printf("| page\t| frame\t|\n");
	printf(" ---------------\n");
	for(int i=0;i<p->size/frame_size;i++)
	{
		printf("|   %d\t|  %d\t|\n", p->page[i].f_no, p->page[i].alloted_frame->st_add);
		printf(" ---------------\n");
	}
	printf("\n");
}

void display_frame(node_frame* head)
{
	printf("Display FraMes\n");
	node_frame* itr;
	itr=head;
	printf(" _______\n");
	while(itr!=NULL)
	{
		if(itr->p==NULL)
			printf("|%d  \t|%d\n",itr->alloted, itr->st_add);
		else
			printf("|%d  %s\t|%d\n",itr->alloted,itr->p->process, itr->st_add);
		printf("|_______|\n");
		itr=itr->next;
	}
}

																			//main
int main(void)
{
	int phy_mem, frame_size;
	node_frame *head_frame=NULL;
	node_process *head_process=NULL;
	printf("enter physical memory size : ");
		scanf("%d", &phy_mem);
	printf("enter frame size : ");
		scanf("%d", &frame_size);
	head_frame=create_frames(head_frame, phy_mem, frame_size);
																			//getting free frames
	free_frame *head_free_frame=NULL;
	node_frame *traverse=head_frame;
	free_frame *itr_ff;
	while(traverse!=NULL)
	{
		if(traverse->alloted==0)
		{
			free_frame* new_free_frame=create_free_frame();
			new_free_frame->frame=traverse;
			if(head_free_frame==NULL)
			{
				head_free_frame=new_free_frame;
				itr_ff=head_free_frame;
			}
			else
			{
				itr_ff->next=new_free_frame;
				itr_ff=itr_ff->next;
			}
		}
		traverse=traverse->next;
	}
																				//paging 
	while(1)
	{
		int option;
		printf("1--Process Request\n2 --Deallocation\n3 --Page Table display for all input process\n4 --Free frame list\n5 --display frame\n6 --exit\nenter option : ");
			scanf("%d", &option);
		if(option==1)
		{
			node_process * itr, *new;
			new=create_process();
			if(new->size<frame_size)
				new->size=frame_size;
			else if(new->size%2!=0)
				new->size+=1;
			else if(new->size>phy_mem)
			{
				printf("request size is greater than phy mem\n");
				continue;
			}
			if(head_process==NULL)
				head_process=new;
			else
			{	
				itr=head_process;
				while(itr->next!=NULL)
					itr=itr->next;
				itr->next=new;
			}
			display_process(head_process);
																				//allocate frames for process with pages
			for(int i=0;i<new->size/frame_size;i++)
			{
				new->page[i].f_no=i;
				new->page[i].alloted_frame=head_free_frame->frame;
				head_free_frame->frame->alloted=1;
				head_free_frame->frame->p=new;
				head_free_frame=remove_alloted_frame(head_free_frame);
			}
		}
																				//deallocate 
		else if(option==2)
		{
			char process[20];
			printf("enter process id : ");
				scanf("%s", process);
			head_process=remove_process(head_process, process, frame_size, head_free_frame);
			display_process(head_process);
		}
																				//display all pages
		else if(option==3)
		{
			node_process *itr;
			itr=head_process;
			if(itr==NULL)
				printf("no process\n");
			else
				while(itr!=NULL)
				{	
					display_page(itr, frame_size);
					itr=itr->next;
				}		
		}
																				//display free frames
		else if(option==4)
		{
			display_free_frame(head_free_frame);
		}
		else if(option==5)
		{
			display_frame(head_frame);
		}
		else if(option ==6)
		{
			break;
		}
		
	}
	printf("program ended\n");	
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex9$ gcc paging.c -op
an@aswin:~/Desktop/sem4/os_labexp/ex9$ ./p
enter physical memory size : 10
enter frame size : 2
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 1
enter process id size : p1 4
Display ProCess
p1 4
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 3
page table of process p1
 ---------------
| page	| frame	|
 ---------------
|   0	|  0	|
 ---------------
|   1	|  2048	|
 ---------------

1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 4
Displaying free frames
-------- -------- -------- 
|4096	|6144	|8192	|
-------- -------- -------- 
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 5
Display FraMes
 _______
|1  p1	|0
|_______|
|1  p1	|2048
|_______|
|0  	|4096
|_______|
|0  	|6144
|_______|
|0  	|8192
|_______|
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 1
enter process id size : p2 2
Display ProCess
p1 4
p2 2
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 3
page table of process p1
 ---------------
| page	| frame	|
 ---------------
|   0	|  0	|
 ---------------
|   1	|  2048	|
 ---------------

page table of process p2
 ---------------
| page	| frame	|
 ---------------
|   0	|  4096	|
 ---------------

1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 4
Displaying free frames
-------- -------- 
|6144	|8192	|
-------- -------- 
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 5
Display FraMes
 _______
|1  p1	|0
|_______|
|1  p1	|2048
|_______|
|1  p2	|4096
|_______|
|0  	|6144
|_______|
|0  	|8192
|_______|
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 2
enter process id : p2
Display ProCess
p1 4
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 3
page table of process p1
 ---------------
| page	| frame	|
 ---------------
|   0	|  0	|
 ---------------
|   1	|  2048	|
 ---------------

1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 4
Displaying free frames
-------- -------- -------- 
|6144	|8192	|4096	|
-------- -------- -------- 
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 5
Display FraMes
 _______
|1  p1	|0
|_______|
|1  p1	|2048
|_______|
|0  p2	|4096
|_______|
|0  	|6144
|_______|
|0  	|8192
|_______|
1--Process Request
2 --Deallocation
3 --Page Table display for all input process
4 --Free frame list
5 --display frame
6 --exit
enter option : 6
program ended
*/
