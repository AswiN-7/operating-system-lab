#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_I 20
int main(void)
{
	int resource[MAX_I];
	int max_need[MAX_I][MAX_I];
	int allocation[MAX_I][MAX_I];
	int need[MAX_I][MAX_I];
	int available[MAX_I];
	int tot_resource,tot_process;
	int order_job[MAX_I],ojc;
	int visited[MAX_I]={0};
	printf("enter total number resources : ");
	scanf("%d",&tot_resource);
	//resources
	/*
	for(int i=0;i<tot_resource;i++)
	{
		printf("enter instances of resourece %d : ", i+1);
		scanf("%d",&resource[i]);
	}
	*/
	
	printf("enter totla number of process : ");
	scanf("%d",&tot_process);
	//total  process max need
	for(int i=0;i<tot_process;i++)
	{
		for(int j=0;j<tot_resource;j++)
		{	
			printf("enter maximum need of resource %d to process %d :  ",j+1, i+1);
			scanf("%d",&max_need[i][j]);
		}
	}
	//displaying max need
	printf("max need\n");
	for(int i=0;i<tot_process;i++)
	{
		printf("process %d :",i+1);
		for(int j=0;j<tot_resource;j++)
			printf("%d ",max_need[i][j]);
		printf("\n");
	
	}
	//allocation
	for(int i=0;i<tot_process;i++)
	{
		for(int j=0;j<tot_resource;j++)
		{	
			printf("enter how many instances of resource %d allocated to process %d :  ",j+1, i+1);
			scanf("%d",&allocation[i][j]);
		}
	}
	//displaying allocated
	printf("allocation \n");
	for(int i=0;i<tot_process;i++)
	{
		printf("process %d :",i+1);
		for(int j=0;j<tot_resource;j++)
			printf("%d ",allocation[i][j]);
		printf("\n");
	
	}
	//need
	for(int i=0;i<tot_process;i++)
	{
		for(int j=0;j<tot_resource;j++)
		{
			need[i][j]=max_need[i][j]-allocation[i][j];
		}
	}
	//displaying need
	printf("need \n");
	for(int i=0;i<tot_process;i++)
	{
		printf("process %d :",i+1);
		for(int j=0;j<tot_resource;j++)
			printf("%d ",need[i][j]);
		printf("\n");
	
	}
	for(int i=0;i<tot_resource;i++)
	{
		printf("enter available instances of resource[%d] ",i+1);
		scanf("%d",&available[i]);
	}
	//display available
	printf("availble\n");
	for(int i=0;i<tot_resource;i++)
	{
		printf("%d ",available[i]);
	}
 
	//safe sequence
	while(ojc!=tot_process)
	{
		int i,j,k;
		for( i=0;i<tot_process;i++)
		{
			for(j=0;j<tot_resource;j++)
			{
				if(need[i][j]>available[j])
				break;
			}
			if(j==tot_resource&&visited[i]!=1)
			{
				for(k=0;j<tot_resource;j++)
				{
					available[k]+=allocation[i][k];
				}
				visited[i]=1;
				order_job[ojc]=i;
				ojc++;
			}
		}		
	}
	for(int i=0;i<tot_process;i++)
	{
		printf("%d ",order_job[i]);
	}
	
	
	
}
