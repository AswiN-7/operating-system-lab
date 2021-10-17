#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct file file;
typedef struct block block;

struct file
{
	char name[20];
	int size;
	block* alloted_block;
	file* next;
	int* in_blocks;
};
 
struct block 
{
	int block_id;
	file* f;
	block* next;
	block*next_file_block;
};

block* create_blocks(block*head, int totalsize,int blocksize)
{
	block*itr;
	for(int i=0;i<totalsize/blocksize;i++)
	{
		block*new_block=(block*)malloc(sizeof(block));
		new_block->block_id=i;
		new_block->f=NULL;
		new_block->next=NULL;
		new_block->next_file_block=NULL;
		if(i==0)
		{
			head=new_block;
			itr=head;
		}
		else
		{
			itr->next=new_block;
			itr=new_block;
		}
	}
	return head;	
}

file* create_files(file*head, int total)
{
	file*itr;
	for(int i=0;i<total;i++)
	{
		file*new_file=(file*)malloc(sizeof(file));
		printf("enter file name size");
			scanf("%s %d", new_file->name, &new_file->size);
		new_file->alloted_block=NULL;
		if(i==0)
		{
			head=new_file;
			itr=head;
		}
		else
		{
			itr->next=new_file;
			itr=new_file;
		}
	}
	return head;	
}

void display_files(file*head, int choice)
{
	file*itr_file;
	itr_file=head;
	while(itr_file!=NULL)
	{
		if(choice==1)
		{
			if(itr_file->alloted_block!=NULL)
				printf("file name:\t%s\nfile size:\t%d\nalloted block %d\n", itr_file->name, itr_file->size, itr_file->alloted_block->block_id);
			else
				printf("file name : %s\nfile size : %d\nalloted block : - \n\n", itr_file->name, itr_file->size);
		}
		else if(choice==2)
		{	
			
			block*itr=itr_file->alloted_block;
			while(itr!=NULL)
			{
				if(itr->next_file_block!=NULL)
				printf("file name:\t%s\nfile size:\t%d\nalloted block %d\n", itr->f->name, itr->f->size, itr->next_file_block->block_id);
				else
				printf("file name : %s\nfile size : %d\nalloted block : - \n\n", itr->f->name, itr->f->size);		
				itr=itr->next;
			}
		}
		else if(choice==3)
		{	
			block*itr2=itr_file->alloted_block;
			//int i=0;
			printf("file name:\t%s\n", itr_file->name);
			//while(itr2!=NULL)
			for(int i=0; itr_file->in_blocks[i]!=0&& itr_file->in_blocks[i+1]!=0;i++)
			{
				printf("%d\n", itr_file->in_blocks[i++]);
				itr2=itr2->next_file_block;
			}
		}
		itr_file=itr_file->next;
	}
}
void display_blocks(block*head)
{
	block*itr;
	itr=head;
	while(itr!=NULL)
	{	
		if(itr->f!=NULL)
			printf("block id :\t%d\nfile alloted :\t%s\n\n", itr->block_id, itr->f->name);
		else
			printf("block id :\t%d\nfile alloted :\t-\n\n", itr->block_id);
		itr=itr->next;
	}
}
int random_number(int lower, int upper)
{
	int rnum=rand();
	printf("%d\n", rnum);
	rnum=(rand()%(upper-lower+1))+lower;
	return rnum;
}

void continuous_allocation(int totalsize, int blocksize, block*block_head, file*file_head)
{
	file*file_itr=file_head;
	int count_rnum=0, random_t=4;
	while(file_itr!=NULL)
	{
		block*block_itr, *block_itrm;
		int rnum, ca;
		while(1)
		{	
				if(count_rnum==random_t)
					rnum=0;
				else
				{	sleep(1);
					rnum=random_number(0,totalsize/blocksize);
				}
				printf("%d\n", rnum);
				block_itr=block_head;
				for(int i=0;i<rnum;i++)
					block_itr=block_itr->next;
				block_itrm=block_itr;
				int check_size=0;
				ca=0;
				while(block_itr!=NULL)
				{		
					if(check_size==file_itr->size)
					{
						ca=1;
						count_rnum=-1;
						break;
					}
					if(block_itr->f==NULL)
					{
						check_size+=blocksize;	
					}
					else
					{
						check_size=0;
						block_itrm=block_itr;
					}
					block_itr=block_itr->next;
				}
				if(count_rnum==-1||count_rnum==random_t)
					break;
				count_rnum++;
			}
			if(ca==1)
			{
				file_itr->alloted_block=block_itrm;
				for(int i=0;i<file_itr->size;i+=blocksize)
				{
					block_itrm->f=file_itr;
					block_itrm=block_itrm->next;
				}
			}
			else
				printf("size is not enough\n");	
		      file_itr=file_itr->next;
	}
}

void linked_allocation(int totalsize, int blocksize, block*block_head, file*file_head)
{
	printf("in la\n");
	int totalblocks=totalsize/blocksize;
	file*file_itr=file_head;
	int count_rnum, random_t=4, alloted_blocks=0;
	int* blocks=(int*)malloc(sizeof(int)*(totalsize/blocksize));
	while(file_itr!=NULL)
	{
		printf("in file\n");
		int* blocks_temp=(int*)malloc(sizeof(int)*(totalsize/blocksize));
		for(int i=0;i<alloted_blocks;i++)
			blocks_temp[i]=blocks[i];
		printf("temp blocks is alloted %d\n", blocks_temp[2]);
		int alloted_blocks_temp=alloted_blocks;
		block*block_itr, *block_itrm;
		int rnum, ca;
		for(int i=0;i<file_itr->size;i+=blocksize)
		{	
			printf("in for loop i=%d\n", i);
			count_rnum=0;
			int itr_num=0;
			while(1)
			{	
				printf("in while loop %d\n", count_rnum);
				if(count_rnum>=random_t)
				{
					rnum=itr_num++;
				}
				else
				{
					rnum=random_number(0,totalsize/blocksize);
					printf("random number %d\n", rnum);
				}
				count_rnum++;
				int present=0;
				for(int j=0;j<alloted_blocks_temp;j++)
				{
					if(blocks_temp[j]==rnum)
					{
							present=1;
							printf("this r num is already present\n");
							break;
					}
				}
				if(present==0)
				{
					blocks_temp[++alloted_blocks_temp]=rnum;
					break;
				}
			}
			
		}
		block*temp=NULL;
		printf("thing completed\n");
		file_itr->in_blocks=(int*)malloc(sizeof(int)*(totalsize/blocksize-alloted_blocks));
		for(int i=alloted_blocks;i<alloted_blocks_temp;i++)
		{
			block*block_itr_temp=block_head;
			blocks[i]=blocks_temp[i];
			file_itr->in_blocks[i-alloted_blocks]=blocks_temp[i];
			printf("new numbers are added\n");
			for(int j=0;j<blocks_temp[i];j++)
			{

				block_itr_temp=block_itr_temp->next;
			}
			printf("block_itr_temp is moved to respective block\n");
			if(i==alloted_blocks)
			{
				file_itr->alloted_block=block_itr_temp;
			}
			printf("1\n");
			if(temp==NULL)
				temp=block_itr_temp;
			else
			{
				while(temp!=NULL)
				{
					printf("temp\n");
					temp=temp->next_file_block;
				}
			}
			printf("2\n");
			temp=block_itr_temp;
			block_itr_temp->f=file_itr;
		}

		file_itr=file_itr->next;
		alloted_blocks=alloted_blocks_temp;
		printf("end\n");
	}
	
}
int main()
{
	int totalsize, blocksize;
	int totalfiles;

	printf("enter total size block size :");
		scanf("%d %d", &totalsize, &blocksize);

	//display_blocks(block_head);
	printf("enter total number of file : ");
		scanf("%d", &totalfiles);


	//display_files(file_head, 0);
	int choice;
	while(1)
	{
		printf("1 -- continuous\n4 --exit\nenter your choice : ");
			scanf("%d", &choice);
		if(choice==1)
		{
			block*block_head=NULL;
			file*file_head=NULL;
			block_head=create_blocks(block_head, totalsize, blocksize);
			file_head=create_files(file_head, totalfiles);
			continuous_allocation(totalsize, blocksize, block_head, file_head);
			display_files(file_head, choice);
			display_blocks(block_head);
		}
		else if(choice==2)
		{
			block*block_head=NULL;
			file*file_head=NULL;
			block_head=create_blocks(block_head, totalsize, blocksize);
			file_head=create_files(file_head, totalfiles);
			linked_allocation(totalsize, blocksize, block_head, file_head);
			//display_files(file_head, choice);
			display_blocks(block_head);
				
		}
		else if(choice==3)
		{
			block*block_head=NULL;
			file*file_head=NULL;
			block_head=create_blocks(block_head, totalsize, blocksize);
			file_head=create_files(file_head, totalfiles);
			linked_allocation(totalsize, blocksize, block_head, file_head);
			display_files(file_head, choice);
			display_blocks(block_head);
		}
		else 
			break;
	}
	//display_blocks(block_head);
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex12$ gcc 1027_allocation.c -oa
an@aswin:~/Desktop/sem4/os_labexp/ex12$ ./a
enter total size block size :16 2
enter total number of file : 3
1 -- continuous
4 --exit
enter your choice : 1
enter file name sizef1 4
enter file name sizef2 2
enter file name sizef3 2
1804289383
7
1681692777
7
1957747793
7
719885386
3
596516649
1
1025202362
4
file name:	f1
file size:	4
alloted block 3
file name:	f2
file size:	2
alloted block 1
file name:	f3
file size:	2
alloted block 4
block id :	0
file alloted :	-

block id :	1
file alloted :	f2

block id :	2
file alloted :	-

block id :	3
file alloted :	f1

block id :	4
file alloted :	f3

block id :	5
file alloted :	-

block id :	6
file alloted :	-

block id :	7
file alloted :	-

1 -- continuous
4 --exit
enter your choice : 4
an@aswin:~/Desktop/sem4/os_labexp/ex12$ 


*/
