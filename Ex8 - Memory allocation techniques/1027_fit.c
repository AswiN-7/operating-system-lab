#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node_process{
    char process[20];
    int size;
};
typedef struct node_process node_process;

struct node_partition{
    char part[20];
    int st_add;
    int ed_add;
    int alloted;
    struct node_process p;
    struct node_partition *next;
};
typedef struct node_partition node_partition;

node_partition* create_partition(node_partition* head);
void traverse(node_partition* head);
node_partition* first_fit(node_partition* head, node_process p);
node_partition* best_fit(node_partition* head, node_process p);
node_partition* worst_fit(node_partition* head, node_process p);
node_partition* create_node_partition();
void fit(int op, node_partition* head);
node_partition* put_process(node_partition* itr, node_process p);
node_partition* coalice(node_partition* head);
node_partition* deallocate(node_partition* head);

node_partition* create_node_partition()
{
    node_partition* new=(node_partition*)malloc(sizeof(node_partition));
    new->alloted=0;
    new->next=NULL;
    return new; 
}

int main (void)
{
	node_partition* head=NULL;
	node_partition *temp, *itr;
	int tot_p, op;
	char p[10];
	printf("enter total partition : ");
	    scanf("%d", &tot_p);
	for(int i=0;i<tot_p;i++)
	{
        head=create_partition(head);	    
	}
	traverse(head);  
	while(1)
	 {
	 	printf("1-- FIRST FIT\n2 --BEST FIT\n3 --WORST FIT\n0 --EXIT\nenter your choice : ");
	 		scanf("%d", &op);
	 	if(op==0)
	 		break;
	 	fit(op, head);	
	 }	 
}

node_partition* create_partition(node_partition* head)
{
    node_partition*temp, *itr; char process[20];
    temp=create_node_partition();
    printf("enter partition : ");
        scanf("%s", temp->part);
    printf("enter starting and ending address : ");
        scanf("%d %d", &temp->st_add, &temp->ed_add);
        printf("after input\n");
    if(head==NULL)
        head=temp;
    else
    {
        itr=head;
        while(itr->next!=NULL)
            itr=itr->next;
        itr->next=temp;
    }
    printf("create p completed\n");
    return head;
}
	
void fit(int op, node_partition* head)
{
	while(1)
	{
		if(op==1)
		{
			int choice;
			printf("1 --process\n2 --deallocate\n3 --coalice\n4 --Display\n0 --exit return to main\nenter choice : ");
				scanf("%d", &choice);
			if(choice==0)
	      		break;
			else if(choice==1)
			{
	    			node_process p;
	    			printf("enter process id : ");
	    				scanf("%s", p.process);
	    			printf("enter size required : ");
	    				scanf("%d", &p.size);
	    			head=first_fit(head, p);
	    			traverse(head);
	    		}
	    		else if(choice==2)
	    		{
	    			head=deallocate(head);
	    		}
	    		else if(choice==3)
	    		{
	    			head=coalice(head);
	    		}
	    		else if(choice==4)
	    		{
	    			traverse(head);
	    		}	    
	     }
	     else if (op==2)
	     {
	     			int choice;
			printf("1 --process\n2 --deallocate\n3 --coalice\n4 --Display\n0 --exit return to main\nenter choice : ");
			scanf("%d", &choice);
			if(choice==0)
	      		break;
			else if(choice==1)
			{
	    			node_process p;
	    			printf("enter process id : ");
	    				scanf("%s", p.process);
	    			printf("enter size required : ");
	    				scanf("%d", &p.size);
	    			head=best_fit(head, p);
	    			traverse(head);
	    		}
	    		else if(choice==2)
	    		{
	    			head=deallocate(head);
	    		}
	    		else if(choice==3)
	    		{
	    			head=coalice(head);
	    		}
	    		else if(choice==4)
	    		{
	    			traverse(head);
	    		}
	     }
	     else if(op==3)
	     {
	     		int choice;
			printf("1 --process\n2 --deallocate\n3 --coalice\n4 --Display\n0 --exit return to main\nenter choice : ");
			scanf("%d", &choice);
			if(choice==0)
	      		break;
			else if(choice==1)
			{
	    			node_process p;
	    			printf("enter process id : ");
	    				scanf("%s", p.process);
	    			printf("enter size required : ");
	    				scanf("%d", &p.size);
	    			head=worst_fit(head, p);
	    			traverse(head);
	    		}
	    		else if(choice==2)
	    		{
	    			head=deallocate(head);
	    		}
	    		else if(choice==3)
	    		{
	    			head=coalice(head);
	    		}
	    		else if(choice==4)
	    		{
	    			traverse(head);
	    		}

	     }
	}
}          
node_partition* first_fit(node_partition* head, node_process p)
{
    node_partition* itr, *new;
    itr=head;
    printf("\t\tFIRST FIT\n");
    if(head==NULL)
    {
        printf("enter there is no partition \n");
        return head;
    }
    else
    {
        while(itr!=NULL)
        {
            if(itr->alloted==0)
            {
                if(p.size<=(itr->ed_add-itr->st_add))
                {
                        if(p.size==(itr->ed_add-itr->st_add))
                        {
                        	itr->p=p;
                        	itr->alloted=1;
                        	    traverse(head);
                        	return head;
                        }
                        else
                        {
                        	itr=put_process(itr, p);
                        	return head;
                        }
                }
                else
                {
                	itr=itr->next;
                }
            }
            else
            {
            	itr=itr->next;
            }        
        }    
    }
    printf("not enough space is having \n");
    return head;
}
node_partition* best_fit(node_partition* head, node_process p)
{
	node_partition* itr, *new, *best=NULL;
	int lss=999;
    	itr=head;
    	printf("\t\tBeSt fIt\n");
    	if(head==NULL)
    	{
      	  printf("enter there is no partition \n");
      	  return head;
    	}
    	else
    	{
    		while(itr!=NULL)
    		{
    			if(itr->alloted==0)
    			{
    				if(p.size<=(itr->ed_add-itr->st_add)&&(itr->ed_add-itr->st_add)<lss)
    				{
    					best=itr;
    					lss=itr->ed_add-itr->st_add;
    				}
    			}
    			itr=itr->next;
    		}
    		if(best==NULL)
    		{
			   printf("not enough space is having \n");
			   return head;
    		}
    		else
    		{
    			if(best->ed_add-best->st_add==p.size)
    			{
    				best->alloted=1;
    				best->p=p;
    			}
    			else
	    			best=put_process(best, p);
    			return head;
    		}
    	}
}

node_partition* worst_fit(node_partition* head, node_process p)
{
	node_partition* itr, *new, *worst=NULL;
	int lss=0;
    	itr=head;
    	printf("\t\tWORST FIT\n");
    	if(head==NULL)
    	{
      	  printf("enter there is no partition \n");
      	  return head;
    	}
    	else
    	{
    		while(itr!=NULL)
    		{
    			if(itr->alloted==0)
    			{
    				if(p.size<=(itr->ed_add-itr->st_add)&&(itr->ed_add-itr->st_add)>lss)
    				{
    					worst=itr;
    					lss=itr->ed_add-itr->st_add;
    				}
    			}
    			itr=itr->next;
    		}
    		if(worst==NULL)
    		{
			   printf("not enough space is having \n");
			   return head;
    		}
    		else
    		{
    			if(worst->ed_add-worst->st_add==p.size)
    			{
    				worst->alloted=1;
    				worst->p=p;
    			}
    			else
	    			worst=put_process(worst, p);
    			return head;
    		}
    	}
}

node_partition* put_process(node_partition* itr, node_process p)
{
			itr->alloted=1;
                  itr->p=p;
                  node_partition* new=create_node_partition();
                  strcpy(new->part, "H");
			new->st_add=itr->st_add+p.size;
                   new->ed_add=itr->ed_add;
                  new->next=itr->next;
                   itr->ed_add=itr->st_add+p.size;
                   itr->next=new;
                   return itr;
}

node_partition* coalice(node_partition* head)
{
	node_partition* itr;
	itr=head;
	while(itr!=NULL)
	{
		if(itr->alloted==0)
		{
			if(itr->next!=NULL&&itr->next->alloted==0)
			{
				itr->ed_add+=itr->next->ed_add-itr->next->st_add;
				itr->next=itr->next->next;
			}
			else
				itr=itr->next;
		}
		else
			itr=itr->next;
	}
	traverse(head);
	return head;
}
node_partition* deallocate(node_partition* head)
{
	node_partition* itr;
	itr=head;
	while(itr!=NULL)
	{
		itr->alloted=0;
		itr=itr->next;
	}
	return head;
}


void traverse(node_partition* head)
{
    node_partition* p_line=head, *p=head;
    printf("traverse\n");
    while(p!=NULL)
    {
        printf("%d \t", p->st_add);
        p=p->next;
    }
    printf("\n");
    p=head;
    
    while(p_line!=NULL)
    {
    	printf("---------");
    	p_line=p_line->next;
    }
    printf("\n");
    while(p!=NULL)
    {
        printf("|%s %d %s|", p->part,p->alloted,p->p.process);
        p=p->next;
    }
    printf("\n");
    p_line=head;
    while(p_line!=NULL)
    {
    	printf("---------");
    	p_line=p_line->next;
    }
    printf("\n");
    p=head;
    while(p!=NULL)
    {
        printf("%d\t",p->ed_add);
        p=p->next;
    }
    printf("\n");
    p=head;
    while(p!=NULL)
    {
        printf("%s ", p->p.process);
        p=p->next;
    }
    printf("\n");
}

/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex8$ gcc fit.c -of
an@aswin:~/Desktop/sem4/os_labexp/ex8$ ./f
enter total partition : 3
h1
100 200
h2
300 400
h3
400 450enter partition : enter starting and ending address : after input
create p completed
enter partition : enter starting and ending address : after input
create p completed
enter partition : enter starting and ending address : 
after input
create p completed
traverse
100 	300 	400 	
---------------------------
|h1 0 ||h2 0 ||h3 0 |
---------------------------
200	400	450	
   
1-- FIRST FIT
2 --BEST FIT
3 --WORST FIT
0 --EXIT
enter your choice : 1
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 1
enter process id : p1
enter size required : 30
		FIRST FIT
traverse
100 	130 	300 	400 	
------------------------------------
|h1 1 p1||H 0 ||h2 0 ||h3 0 |
------------------------------------
130	200	400	450	
p1    
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 1
enter process id : p2
enter size required : 50
		FIRST FIT
traverse
100 	130 	180 	300 	400 	
---------------------------------------------
|h1 1 p1||H 1 p2||H 0 ||h2 0 ||h3 0 |
---------------------------------------------
130	180	200	400	450	
p1 p2    
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 
1
enter process id : p3
enter size required : 80
		FIRST FIT
traverse
100 	130 	180 	300 	380 	400 	
------------------------------------------------------
|h1 1 p1||H 1 p2||H 0 ||h2 1 p3||H 0 ||h3 0 |
------------------------------------------------------
130	180	200	380	400	450	
p1 p2  p3   
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 2
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 4
traverse
100 	130 	180 	300 	380 	400 	
------------------------------------------------------
|h1 0 p1||H 0 p2||H 0 ||h2 0 p3||H 0 ||h3 0 |
------------------------------------------------------
130	180	200	380	400	450	
p1 p2  p3   
1 --process
2 --deallocate
3 --coalice
4 --Display
0 --exit return to main
enter choice : 0
1-- FIRST FIT
2 --BEST FIT
3 --WORST FIT
0 --EXIT
enter your choice : 0
*/
