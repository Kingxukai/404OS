#include "../include/unistd.h"
#include "../include/printf.h"
#include "../include/lib.h"
typedef struct _node {
	struct node_ *next;
	char ch;
	int in;
	long lo;
	short sh;
}*NODE,Node;

void task2()
{
	printf("task%d running\n",getpid());
	printf("my father is %d\n",getppid());
	exit();
}

void task3()
{
	int t = 5;
	printf("my father is %d\n",getppid());
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task4()
{
	printf("task%d running\n",getpid());
	printf("my father is %d\n",getppid());
	printf("task%d running\n",getpid());
	while(1)
	{
	
	}
}

void task1()
{
	printf("task%d is running\n",getpid());
	pid_t pid2,pid3,pid4;
	if((pid2 = fork()) == 0)
	{
		execve(task2,NULL,NULL);
	}
	else if((pid3 = fork()) == 0)
	{
		execve(task3,NULL,NULL);
	}
	else if((pid4 = fork()) == 0)
	{
		execve(task4,NULL,NULL);
	}
	else
	{
		printf("task%d has created\n",pid2);
		printf("task%d has created\n",pid3);
		printf("task%d has created\n",pid4);
		waitpid(pid3,NULL,0);
		printf("here is father process\n");
	}
	while(1)
	{
	
	}
}
