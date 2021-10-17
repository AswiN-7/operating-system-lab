#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<pthreads.h>
#define MAX_INT 20

int num[MAX_INT];										//stores input(cmd)

void *max_find(void *arg);
void* min_find(void*arg);
void* avg_find(void*arg);

int main(int argc, char* argv[])
{
	printf("argc -- %d\n", argc);
	if(argc<=1)
	{
		printf("invalid cmd arguments\n");
	}
	else
	{
		pthread_t newthread1;
		pthread_t newthread2;
		pthread_t newthread3;
		int counter;
		int size=argc-1;
		for(int i=1;i<argc;i++)						//converting argv[] into integer
		{
			counter=1;
			for(int j=strlen(argv[i])-1;j>=0;j--)
			{
				num[i-1]+=(argv[i][j]-'0')*counter;
				counter*=10;
			}
		}
		for(int i=0;i<argc-1;i++)					//printing cmd inputs as integer
		{
			printf("%d ", num[i]);
		}
		printf("\n");
		void *max_res;
		void *min_res;
		void *avg_res;
		
		pthread_create(&newthread1, NULL, max_find,&size);
		pthread_create(&newthread2, NULL, min_find,&size);
		pthread_create(&newthread3, NULL, avg_find,&size);
		
		pthread_join(newthread1,&max_res);
		pthread_join(newthread2,&min_res);
		pthread_join(newthread3,&avg_res);
			
		printf("%d max\n", *(int*)max_res);
		printf("%d min\n", *(int*)min_res);
		printf("%d avg\n", *(int*)avg_res);
	}
}

void* max_find(void*arg)
{
	int *max = (int*)malloc(sizeof(int)) ;
	*max=num[0];
	int *size=(int *)arg;
	for(int i=1;i<=*size;i++)
	{
		if(*max<num[i])
			*max=num[i];		
	}
	return max;
}

void* min_find(void*arg)
{
	int* min=(int*)malloc(sizeof(int));
	*min=num[0];
	int *size=(int*)arg;
	for(int i=1;i<*size;i++)
	{
		if(*min>num[i])
			*min=num[i];
	}
	return min;
}
void* avg_find(void*arg)
{
	int *avg_num=(int*)malloc(sizeof(int));
	int* size=(int*)arg;
	*avg_num=num[0];
	for(int i=1;i<*size;i++)
	{
			*avg_num+=num[i];
	}
	*avg_num/=*size;
	return avg_num;
}
/*
SAMPLE I/O
an@aswin:~/Desktop/sem4/os_labexp/ex11$ gcc threads.c -ott -lpthread
threads.c: In function ‘main’:
threads.c:45:3: warning: implicit declaration of function ‘pthread_create’ [-Wimplicit-function-declaration]
   pthread_create(&newthread1, NULL, max_find,&size);
   ^~~~~~~~~~~~~~
threads.c:49:3: warning: implicit declaration of function ‘pthread_join’ [-Wimplicit-function-declaration]
   pthread_join(newthread1,&max_res);
   ^~~~~~~~~~~~
an@aswin:~/Desktop/sem4/os_labexp/ex11$ ./tt 90 81 78 95 79 72 85
argc -- 8
90 81 78 95 79 72 85 
95 max
72 min
82 avg

*/
