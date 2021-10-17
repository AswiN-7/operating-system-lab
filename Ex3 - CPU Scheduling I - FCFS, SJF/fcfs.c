#include<stdio.h>
#include<stdlib.h>
#define MAX_JOB 20

struct  job{

				char  job_name[20];
				float at, bt, st,ft, wt, rt, tat;
};

typedef struct job Job;
Job* input_fun(int);
void gantt_chart(Job*jobs[],int total_job);
void display(Job*jobs[],int total);
void process_q(Job*jobs[],int total_job);

int main( void )
{
	int total_job;
	printf("hi\n"); 
	printf("enter total number jobs : ");
	scanf("%d",&total_job);
	Job* jobs[MAX_JOB];
	for(int i=0;i<total_job;i++)
	{
		jobs[i]=input_fun(i);
	}
	process_q(jobs,total_job);
	gantt_chart(jobs,total_job);
	display(jobs,total_job);

}

Job* input_fun(int i)
{
	Job*j=(Job*)malloc(sizeof(Job));
	printf("enter name of the job [ %d ]: ",i+1);
		scanf("%s",j->job_name);
	printf("enter arrival time : ");
		scanf("%f", &j->at);
	printf("enter burst time : ");
		scanf("%f", &j->bt);
	return j;
}


void process_q(Job*jobs[],int total_job)
{
	 int swap=0, swap_inner=0;
	for(int i=0;i<total_job;i++)
	{
		for(int j=i+1;j<total_job;j++)
		{
			if(jobs[i]->at > jobs[j]->at)
			{
				Job*temp=jobs[i];
				jobs[i]=jobs[j];
				jobs[j]=temp;
				printf("sawp hi %d\n",++swap);
			}
		}
	}
}

void gantt_chart(Job*jobs[],int total_job)
{
	int i;
	for(i=0;i<total_job;i++)
	{
		if(i==0)
		{
			jobs[i]->st=0;
			jobs[i]->ft=jobs[i]->bt;
			jobs[i]->wt=jobs[i]->at-jobs[i]->st;
			jobs[i]->rt=jobs[i]->wt;
			jobs[i]->tat=jobs[i]->bt+jobs[i]->wt;
		}
		else
		{
			if(jobs[i]->at<jobs[i-1]->ft)
				jobs[i]->st=jobs[i-1]->ft;				
			else
				jobs[i]->st=jobs[i]->at;
			jobs[i]->ft=jobs[i]->st+jobs[i]->bt;
			jobs[i]->wt=jobs[i]->st-jobs[i]->at;
			jobs[i]->rt=jobs[i]->wt;
			jobs[i]->tat=jobs[i]->bt+jobs[i]->wt;
		}
	}
}
void display(Job*jobs[],int total)
{
	printf("PID\tAT\tBT\tST\tFT\tWT\tRT\tTAT\n");
	for(int j =0; j<total; j++)
	{
		printf("%s\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\t%.0f\n",jobs[j]->job_name,jobs[j]->at,jobs[j]->bt,jobs[j]->st,jobs[j]->ft,jobs[j]->wt,jobs[j]->rt,jobs[j]->tat);
	}
	float avgwt=0,avgtat=0;
	for(int i=0;i<total;i++)
	{
		avgwt+=jobs[i]->wt;
		avgtat+=jobs[i]->tat;
	}
	avgwt=avgwt/total;
	avgtat=avgtat/total;
	printf("average\t\t\t\t%.2f\t%.2f\t%.2f\n",avgwt,avgwt,avgtat);
}

/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex3$ gcc fcfs.c -o1
an@aswin:~/Desktop/sem4/os_labexp/ex3$ ./1
hi
enter total number jobs : 3
enter name of the job [ 1 ]: p1
enter arrival time : 2
enter burst time : 3
enter name of the job [ 2 ]: p2
enter arrival time : 1
enter burst time : 3
enter name of the job [ 3 ]: p3
enter arrival time : 3
enter burst time : 3
sawp hi 1
PID	AT	BT	ST	FT	WT	RT	TAT
p2	1	3	0	3	1	1	4
p1	2	3	3	6	1	1	4
p3	3	3	6	9	3	3	6
average				1.67	1.67	4.67
an@aswin:~/Desktop/sem4/os_labexp/ex3$ 

*/


