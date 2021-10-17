/*
	sjc  -> sorted_job_count
	crt -> current running time
	lft->last finishing time (of each cycle)
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_JOB 20

struct  job{

		char  job_name[20];
		float at, bt, st,ft, wt, rt, tat;
		int visited,finished;
};

typedef struct job Job;
Job* input_fun(int);
void gantt_chart(Job*jobs[],int total_job);
void process_q(Job*jobs[],int total_job);
void display(Job*jobs[],int total);

int main( void )
{
	int total_job;
	printf("hi\n"); 
	printf("enter total number jobs : ");
	scanf("%d",&total_job);
	Job* jobs[MAX_JOB];
	Job*ordered_jobs[MAX_JOB];
	for(int i=0;i<total_job;i++)
	{
		jobs[i]=input_fun(i);
	}
	process_q(jobs,total_job);
	gantt_chart(jobs, total_job);
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
		j->visited=j->finished=0;
	return j;
}

void process_q(Job*jobs[],int total_job)
{ 
		int jtotal=total_job, i=0,crt=0,sjc=0,lft;
		int shortest_job;
		Job*sj;
		while(jtotal!=0)
		{  
			lft=999;
			shortest_job=-1;
			for(int j=i;j<total_job;j++)
			{
					if(jobs[j]->at <=crt)
					{
						if(jobs[j]->bt<lft)
						{
							lft=jobs[j]->bt;
							shortest_job=j;
						}
					}
				
				printf("shortest job at %d loop is %d\n", j,shortest_job);
			}
			if(shortest_job==-1)
				crt++;
			else
			{
				jobs[shortest_job]->visited=1;
				sj=jobs[shortest_job];              //swapping  shorter 
				jobs[shortest_job]=jobs[i];
				jobs[i]=sj;
				i++;
				jtotal--;
				printf("%d jtotal\n",jtotal );
				crt+=sj->bt;
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
	printf("waiting time %f  turnaround time %f\n", avgwt, avgtat);
	avgwt=avgwt/total;
	avgtat=avgtat/total;
	printf("average\t\t\t\t%.2f\t%.2f\t%.2f\n",avgwt,avgwt,avgtat);
}

/*
SAMPLE I/O:
an@aswin:~/Desktop/sem4/os_labexp/ex3$ gcc npsjf.c -o2
an@aswin:~/Desktop/sem4/os_labexp/ex3$ ./2
hi
enter total number jobs : 3
enter name of the job [ 1 ]: p1
enter arrival time : 2
enter burst time : 3
enter name of the job [ 2 ]: p2
enter arrival time : 1
enter burst time : 2
enter name of the job [ 3 ]: p3
enter arrival time : 2
enter burst time : 4
shortest job at 0 loop is -1
shortest job at 1 loop is -1
shortest job at 2 loop is -1
shortest job at 0 loop is -1
shortest job at 1 loop is 1
shortest job at 2 loop is 1
2 jtotal
shortest job at 1 loop is 1
shortest job at 2 loop is 1
1 jtotal
shortest job at 2 loop is 2
0 jtotal
PID	AT	BT	ST	FT	WT	RT	TAT
p2	1	2	0	2	1	1	3
p1	2	3	2	5	0	0	3
p3	2	4	5	9	3	3	7
waiting time 4.000000  turnaround time 13.000000
average				1.33	1.33	4.33

*/


