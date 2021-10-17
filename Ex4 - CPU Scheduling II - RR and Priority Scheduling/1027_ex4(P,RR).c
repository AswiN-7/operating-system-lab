/*
	sjc  . sorted_job_count
	crt . current running time
	all finished(p ,rr)	
	rr-with commands
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_JOB 20

struct  job{

		char  job_name[20];
		int at, bt, st,ft, wt, rt, tat;
		int visited,finished,priority;
};

typedef struct job Job;
void input_fun(int tot,Job j[]);
void gantt_chart(Job jobs[],int total_job);
int process_pp(Job jobs[],int total_job, Job orderd_jobs[]);
int process_npp(Job jobs[],int total_job, Job orderd_jobs[]);
int process_rr(Job jobs[], int total_job, Job ordered_jobs[], int ts);
void display(Job jobs[],int total,int inp_total);

int main( void )
{
	while(1)
	{
		Job jobs[MAX_JOB];
		Job ordered_jobs[MAX_JOB];
		int total_job,tot_ord_job, choice;
	
		printf("1 --NPP\n2 --PP\n3 --RR\n-1 --EXIT\nenter your choice:");
			scanf("%d",&choice);
		
		if(choice==1)
		{
			printf("enter total number jobs : ");
			scanf("%d",&total_job);
			input_fun(total_job, jobs);
			tot_ord_job=process_npp(jobs,total_job, ordered_jobs);
		}
		else if(choice==2)
		{
			printf("enter total number jobs : ");
			scanf("%d",&total_job);
			input_fun(total_job, jobs);
			tot_ord_job=process_pp(jobs,total_job, ordered_jobs);
		}
		else if(choice==3)
		{
		 	int ts;
			printf("enter total number jobs : ");
				scanf("%d",&total_job);
			input_fun(total_job, jobs);
			printf("enter time slot : ");
				scanf("%d",&ts);	
			tot_ord_job=process_rr(jobs,total_job, ordered_jobs, ts);
		}
		else
			break;
		printf("%d\n",tot_ord_job);
		gantt_chart(ordered_jobs, tot_ord_job);
		display(ordered_jobs,tot_ord_job ,total_job);
		
	}
}
void input_fun(int tot,Job j[])
{
	for(int i=0;i<tot;i++)
	{
	printf("enter name of the job [ %d ]: ",i+1);
		scanf("%s",j[i].job_name);
	printf("enter arrival time : ");
		scanf("%d", &j[i].at);
	printf("enter burst time : ");
		scanf("%d", &j[i].bt);
	printf("enter priority : ");
		scanf("%d",&j[i].priority);
		j[i].visited=j[i].finished=0;
		j[i].st=j[i].ft=j[i].wt=j[i].rt=j[i].tat=0;
	}
}

int process_npp(Job jobs[],int total_job,Job ordered_jobs[])
{ 
		int jtotal=total_job, i=0,crt=0,sjc=-1;
		int sj,p;
		while(jtotal!=0)
		{  
			sj=-1;
			p=100;
			for(int j=0;j<total_job;j++)
			{
				if (jobs[j].visited==0)    //eliminate visited jobs
				{
					if(jobs[j].at <=crt)
					{
						if(jobs[j].priority<p)
						{
								sj=j;
								p=jobs[j].priority;
						}
					}
				}
			}
			if(sj==-1)
				crt++;
			else
			{
				ordered_jobs[++sjc]=jobs[sj];
				ordered_jobs[sjc].st=crt;
				ordered_jobs[sjc].ft=ordered_jobs[sjc].st+ordered_jobs[sjc].bt;
				ordered_jobs[sjc].wt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
				ordered_jobs[sjc].rt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
				ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
				jobs[sj].visited=1;
				ordered_jobs[sjc].finished=1;
				
				jtotal--;
				crt+=jobs[sj].bt;
			}	
		}
		return sjc+1;		
}


int process_pp(Job jobs[],int total_job,Job ordered_jobs[])
{ 
	int jtotal=total_job, crt=0, sj =-1, sjc=-1, same_job_checker=-1,p=100;
	int i;
	Job inp_jobs[total_job];
	for(int i=0;i<total_job;i++)
	{
		inp_jobs[i]=jobs[i];
	}
	while(jtotal!=0)
	{
		for(i=0;i<total_job;i++)
		{
			if(inp_jobs[i].bt!=0)
			{
				if(inp_jobs[i].at<=crt)
				{
					if(inp_jobs[i].priority<p)
					{
						sj=i;
						p=inp_jobs[i].priority;
					}
				}
			}
		}//for
		if(sj==-1)
			crt++;
		else
		{
			if(same_job_checker==sj)
			{
				ordered_jobs[sjc].bt++;
				inp_jobs[sj].bt--;
				if(inp_jobs[sj].bt==0)
				{
					crt++;
					jtotal--;
					ordered_jobs[sjc].ft=crt;
					sj=-1;
					ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
					ordered_jobs[sjc].finished=1;
					p=100;
				}
				else
				{
					crt++;
					p=inp_jobs[sj].priority;
					ordered_jobs[sjc].ft=crt;
					inp_jobs[sj].ft=crt;
				}
				
			}
			else
			{
				same_job_checker=sj;
				
				ordered_jobs[++sjc]=inp_jobs[sj];
				ordered_jobs[sjc].st=crt;
				ordered_jobs[sjc].bt=1;
				ordered_jobs[sjc].ft=crt+1;

				if(inp_jobs[sj].visited==0)
				{
					inp_jobs[sj].ft=crt+1;
					inp_jobs[sj].wt=crt-inp_jobs[sj].at;
					ordered_jobs[sjc].wt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
					ordered_jobs[sjc].rt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
				}
				else
				{
					ordered_jobs[sjc].wt=inp_jobs[sj].wt+ordered_jobs[sjc].st-inp_jobs[sj].ft;
					inp_jobs[sj].wt=ordered_jobs[sjc].wt;
					inp_jobs[sj].ft=crt+1;
					
				}
				inp_jobs[sj].bt--;
				if(inp_jobs[sj].bt==0) //process completed
				{
					crt++;
					p=100;
					jtotal--;
					ordered_jobs[sjc].ft=crt;
					sj=-1;
					ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
					ordered_jobs[sjc].finished=1;					
				}
				else
				{
					crt++;
					p=inp_jobs[sj].priority;
				}
				inp_jobs[sj].visited=1; 
			}
		}
		
	}//while
	return sjc+1;
}



int process_rr(Job jobs[], int total_job, Job ordered_jobs[],int ts)
{
	int jtotal=total_job, crt=0, sj =-1, sjc=-1, same_job_checker=-1;
	int i=0;
	Job inp_jobs[total_job];
	for(int i=0;i<total_job;i++)
	{
		inp_jobs[i]=jobs[i];
	}
	while(jtotal!=0)
	{	
		if(inp_jobs[i].bt!=0)
		{	
			if(same_job_checker==i)
			{	
				if(inp_jobs[i].bt<=ts)
				{
					ordered_jobs[sjc].bt+=inp_jobs[i].bt;
					crt+=inp_jobs[i].bt;
					ordered_jobs[sjc].ft=crt;
					ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
					ordered_jobs[sjc].finished=1;
					jtotal--;
					inp_jobs[i].bt=0;
				}
				else
				{
					ordered_jobs[sjc].bt+=ts;
					inp_jobs[i].bt-=ts;
					crt+=ts;
					inp_jobs[i].ft=crt;
					ordered_jobs[sjc].ft=crt;
				}
			}
			else
			{
				same_job_checker=i;
				ordered_jobs[++sjc]=inp_jobs[i];
				ordered_jobs[sjc].st=crt;
				if(inp_jobs[i].visited==0)
				{
					if(inp_jobs[i].bt<=ts)
					{
						ordered_jobs[sjc].bt=inp_jobs[i].bt;
						ordered_jobs[sjc].ft=crt+ordered_jobs[sjc].bt;
						ordered_jobs[sjc].wt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
						ordered_jobs[sjc].rt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
						inp_jobs[i].ft=crt+inp_jobs[i].bt;
						inp_jobs[i].wt=crt-inp_jobs[i].at;						
						crt+=inp_jobs[i].bt;
						inp_jobs[i].bt=0;
						ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
						jtotal--;
						ordered_jobs[sjc].finished=1;
					}					
					else
					{
						ordered_jobs[sjc].bt=ts;
						ordered_jobs[sjc].ft=crt+ordered_jobs[sjc].bt;
						ordered_jobs[sjc].wt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
						ordered_jobs[sjc].rt=ordered_jobs[sjc].st-ordered_jobs[sjc].at;
						inp_jobs[i].bt-=ts;
						inp_jobs[i].ft=ordered_jobs[sjc].ft;
						inp_jobs[i].wt=ordered_jobs[sjc].wt;
						crt+=ts;
					}
					inp_jobs[i].visited=1;
				}
				else
				{
					if(inp_jobs[i].bt<=ts)
					{	
						ordered_jobs[sjc].bt=inp_jobs[i].bt;
						ordered_jobs[sjc].ft=crt+ordered_jobs[sjc].bt;
						ordered_jobs[sjc].wt=inp_jobs[i].wt+ordered_jobs[sjc].st-inp_jobs[i].ft;
						inp_jobs[i].ft=ordered_jobs[sjc].ft;
						inp_jobs[i].wt=ordered_jobs[sjc].wt;
						crt+=inp_jobs[i].bt;
						inp_jobs[i].bt=0;
						jtotal--;
						ordered_jobs[sjc].tat=ordered_jobs[sjc].bt+ordered_jobs[sjc].wt;
						ordered_jobs[sjc].finished=1;
					}
					else
					{
						ordered_jobs[sjc].bt=ts;
						ordered_jobs[sjc].ft=crt+ordered_jobs[sjc].bt;
						ordered_jobs[sjc].wt=inp_jobs[i].wt+ordered_jobs[sjc].st-inp_jobs[i].ft;
						inp_jobs[i].ft=ordered_jobs[sjc].ft;
						inp_jobs[i].wt=ordered_jobs[sjc].wt;
						crt+=ts;
						inp_jobs[i].bt-=ts;
					}
					
				}
			}
			i++;
			if(i==total_job)
				i=0;
		}
		else
		{
			i++;
			if(i==total_job)
				i=0;
		}
	}
	return sjc+1;
}




void gantt_chart(Job  jobs[],int total_job)
{
	int i;
	for(i=0;i<total_job;i++)
	{
		printf("------"); 
	}
	printf("\n");
	for(i=0;i<total_job;i++)
	{
		printf("| %s |",jobs[i].job_name); 
	}
	printf("\n");
	for(i=0;i<total_job;i++)
	{
		printf("------"); 
	}
	printf("\n");
	for(i=0;i<total_job;i++)
	{
		if(jobs[i].st>9)
		printf("%d    ",jobs[i].st);
		else
		printf("%d     ",jobs[i].st); 
	}
	printf("%d\n\n",jobs[i-1].ft);
}

void display(Job jobs[],int total,int inp_total)
{
	float avgwt=0,avgtat=0,avgrt=0;
	printf("PID\tAT\tBT\tPT\tST\tFT\tWT\tRT\tTAT\n");
	for(int j =0; j<total; j++)
	{
printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",jobs[j].job_name,jobs[j].at,jobs[j].bt,jobs[j].priority,jobs[j].st,jobs[j].ft,jobs[j].wt,jobs[j].rt,jobs[j].tat);
	}
	for(int i=0;i<total;i++)
	{
		avgrt+=jobs[i].rt;
		if(jobs[i].finished==1)
		{
			avgwt+=jobs[i].wt;
			avgtat+=jobs[i].tat;
		}
	}
	printf("\navgwt-- %f avgtat-- %f\n", avgwt, avgtat);
	avgwt/=inp_total;
	avgtat/=inp_total;
	avgrt/=inp_total;
	printf("average\t\t\t\t\t%.2f\t%.2f\t%.2f\n",avgwt,avgrt,avgtat);
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex4$ gcc 1027_ex4\(P\,RR\).c -o p
an@aswin:~/Desktop/sem4/os_labexp/ex4$ ./p
1 --NPP
2 --PP
3 --RR
-1 --EXIT
enter your choice:1
enter total number jobs : 3
p1
0
5
3
p2
2
8
1
p3
4
2
2enter name of the job [ 1 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 2 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 3 ]: enter arrival time : enter burst time : enter priority : 
3
------------------
| p1 || p2 || p3 |
------------------
0     5     13    15

PID	AT	BT	PT	ST	FT	WT	RT	TAT
p1	0	5	3	0	5	0	0	5
p2	2	8	1	5	13	3	3	11
p3	4	2	2	13	15	9	9	11

avgwt-- 12.000000 avgtat-- 27.000000
average					4.00	4.00	9.00
1 --NPP
2 --PP
3 --RR
-1 --EXIT
enter your choice:2
enter total number jobs : 3
p1
0
5
3
p2
2
8
1
p3
4
2
2enter name of the job [ 1 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 2 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 3 ]: enter arrival time : enter burst time : enter priority : 
4
------------------------
| p1 || p2 || p3 || p1 |
------------------------
0     2     10    12    15

PID	AT	BT	PT	ST	FT	WT	RT	TAT
p1	0	2	3	0	2	0	0	0
p2	2	8	1	2	10	0	0	8
p3	4	2	2	10	12	6	6	8
p1	0	3	3	12	15	10	0	13

avgwt-- 16.000000 avgtat-- 29.000000
average					5.33	2.00	9.67
1 --NPP
2 --PP
3 --RR
-1 --EXIT
enter your choice:3
enter total number jobs : 3
p1
0
8
0
p2
0
3
0
p3
0
4
0enter name of the job [ 1 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 2 ]: enter arrival time : enter burst time : enter priority : enter name of the job [ 3 ]: enter arrival time : enter burst time : enter priority : 
enter time slot : 2
7
------------------------------------------
| p1 || p2 || p3 || p1 || p2 || p3 || p1 |
------------------------------------------
0     2     4     6     8     9     11    15

PID	AT	BT	PT	ST	FT	WT	RT	TAT
p1	0	2	0	0	2	0	0	0
p2	0	2	0	2	4	2	2	0
p3	0	2	0	4	6	4	4	0
p1	0	2	0	6	8	4	0	0
p2	0	1	0	8	9	6	0	7
p3	0	2	0	9	11	7	0	9
p1	0	4	0	11	15	7	0	11

avgwt-- 20.000000 avgtat-- 27.000000
average					6.67	2.00	9.00
1 --NPP
2 --PP
3 --RR
-1 --EXIT
enter your choice:-1
an@aswin:~/Desktop/sem4/os_labexp/ex4$ 


*/
