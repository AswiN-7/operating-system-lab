/*
	type  -1 directory, 
	type  -2 file, 	
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct file file;
typedef struct directory dir;

struct file{
	char f_name[20];
	long location;
	file*next;
};

struct directory
{
	char d_name[20];
	long location;
	file* files;
	dir*subdir;
	dir* next;
};

file* create_file();
dir* create_dir();
int check_duplicate_file(file* f, char f_name[]);
int check_duplicate_dir(dir* d, char d_name[]);
dir* create_file_or_dir_inside_dir(dir*root, int type);
void display_dir_and_files(dir*d, int space);

																														
int main()																												//menu
{
	int option;
	while(1)
	{
		printf("1 --single level\n2 --tree \n3 --exit\nenter your choice : ");
			scanf("%d", &option);
		dir* root=NULL;
		if(option==1)
		{
			root=create_dir();
			int  choice;
			while(1)
			{
				printf("1 --create new file\n2 --list all files\n3 --back to main\nenter your choice : ");
					scanf("%d", &choice);
				if(choice==1)
				{
					root= create_file_or_dir_inside_dir(root, 2);
				}
				else if(choice==2)
				{
					display_dir_and_files(root, 0);
				}
				else
					break;
			}
						
		}
		else if(option==2)
		{
			root=create_dir();
			int choice;
			while(1)
			{
				printf("1 --create directory\n2 --create file\n3 --list directory and files\n4 --exit\nenter your option : ");
					scanf("%d", &choice);
				if(choice==1)
				{
					root=create_file_or_dir_inside_dir(root, 1);
				}
				else if(choice==2)
				{
					root= create_file_or_dir_inside_dir(root, 2);
				}
				else if(choice==3)
				{
					display_dir_and_files(root, 0);
				}
				
				else if(choice==4)
				{
					break;
				}
			}
		}
		else
			break;
	}	
}

file* create_file()																												//create new files
{
	file* new_file=(file*)malloc(sizeof(file));
	printf("enter file name :");
		scanf("%s", new_file->f_name);
	new_file->location=(long)&new_file;
	new_file->next=NULL;
	return new_file;
}

dir* create_dir()																											//create new directory
{
	dir* new_dir=(dir*)malloc(sizeof(dir));
	printf("enter dir name : ");
		scanf("%s", new_dir->d_name);
	new_dir->files=NULL;
	new_dir->next=NULL;
	new_dir->subdir=NULL;
	return new_dir;
}

int check_duplicate_file(file* f, char f_name[])																	
{
	file* itr;
	itr=f;
	while(itr!=NULL)
	{
		if(strcmp(itr->f_name, f_name)==0)
			return 1;
		itr=itr->next;
	}
	return 0;
}

int check_duplicate_dir(dir* d, char d_name[])
{
	dir* itr;
	itr=d;
	while(itr!=NULL)
	{
		if(strcmp(itr->d_name, d_name)==0)
			return 1;
		itr=itr->next;
	}
	return 0;
}

dir* create_file_or_dir_inside_dir(dir*root, int type)
{
	int choice, i=0;
	dir* dir_itr;
	dir_itr=root->subdir;
	printf("%d --create in current directory\n", i);
	if(dir_itr!=NULL)																	//displAying all directories in current directory
	{
		while(dir_itr!=NULL)
		{
			printf("%d --%s \n", ++i, dir_itr->d_name);
			dir_itr=dir_itr->next;
		}
	}																					//end display
	printf("enter your choice : ");
	scanf("%d", &choice);
	if(choice==0)																		//checking choice
	{
		if(type==1)																	//type file or directory(creation)		here directory
		{
			int dup=1;
			dir* new_dir;
			while(dup!=0)
			{
				 new_dir=create_dir();
			 	dup=check_duplicate_dir(root->subdir, new_dir->d_name);		//checking duplicate dir name
			 	if(dup==1)
			 		printf("directory name is already present\n");
			}			
			if(root->subdir==NULL)
				root->subdir=new_dir;
			else
			{
				dir*temp=root->subdir;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=new_dir;	
			}
		}
		else if(type==2)																//type file or directory(creation)		here file
		{
			int dup=1;
			file* new_file;
			while(dup!=0)
			{
				new_file=create_file();
			 	dup=check_duplicate_file(root->files, new_file->f_name);		////checking duplicate dir file
			 	if(dup==1)
			 		printf("file name is already present\n");
			}
			if(root->files==NULL)
				root->files=new_file;
			else
			{
				file*temp=root->files;
				while(temp->next!=NULL)
					temp=temp->next;
				temp->next=new_file;	
			}
		}
		return root;
	}
	else
	{
		dir_itr=root->subdir;
		if(dir_itr!=NULL)
		{
			for(int j=1;j<choice;j++)
			{	
				dir_itr=dir_itr->next;
			}
		}
		dir_itr=create_file_or_dir_inside_dir(dir_itr, type);								//recursively calling sub directories
		return root;
	}
}

void display_dir_and_files(dir*d, int space)
{
	if(d!=NULL)
	{
		for(int i=0;i<space;i++)
			printf("\t");
		printf("dir: %s\n", d->d_name);
		for(int i=0;i<space;i++)
			printf("\t");
		printf("  file_name\tLocation\n");
		file* itr_f;
		

		if(d->files!=NULL)
		{
			itr_f=d->files;
			while(itr_f!=NULL)
			{
				for(int i=0;i<space;i++)
					printf("\t");
				printf("  ");	
				printf("%s\t%ld",itr_f->f_name, itr_f->location);
				itr_f=itr_f->next;
			}
			printf("\n");
		}
		else
		{
			printf("this dir has no files\n");
		}
		dir* itr_f_shibiling=d->subdir;
		while(itr_f_shibiling!=NULL)
		{
			//sleep(1);
			display_dir_and_files(itr_f_shibiling, space+1);
			itr_f_shibiling=itr_f_shibiling->next;
		}
	}	
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex13$ gcc file.c -of
an@aswin:~/Desktop/sem4/os_labexp/ex13$ ./f
1 --single level
2 --tree 
3 --exit
enter your choice : 2
enter dir name : d1
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 1
0 --create in current directory
enter your choice : 0
enter dir name : s1
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 1
0 --create in current directory
1 --s1 
enter your choice : 0
enter dir name : s1
directory name is already present
enter dir name : s2
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 2
0 --create in current directory
1 --s1 
2 --s2 
enter your choice : 0
enter file name :fileOnD
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 2
0 --create in current directory
1 --s1 
2 --s2 
enter your choice : 2
0 --create in current directory
enter your choice : 0
enter file name :fileOns2
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 1
0 --create in current directory
1 --s1 
2 --s2 
enter your choice : 2
0 --create in current directory
enter your choice : 0
enter dir name : s22
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 3
dir: d1
  file_name	Location  
  fileOnD	140722238848832
	dir: s1
	  file_name	Location
	  this dir has no files
	dir: s2
	  file_name	Location	  
	  fileOns2	140722238848720
		dir: s22
		  file_name	Location
		  this dir has no files
1 --create directory
2 --create file
3 --list directory and files
4 --exit
enter your option : 4
1 --single level
2 --tree 
3 --exit
enter your choice : 3
an@aswin:~/Desktop/sem4/os_labexp/ex13$ 
*/

