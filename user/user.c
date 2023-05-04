#include "../include/unistd.h"
#include "../include/printf.h"

void task2()
{
	printf("task%d running\n",getpid());
	exit();
}

void task3()
{
	int t = 5;
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task4()
{
	printf("task%d running\n",getpid());
	wait();
	printf("task%d running\n",getpid());
}

void task1()
{
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
		//wait();
		printf("here is father process\n");
		printf("task%d is running\n",getpid());
	}
	while(1)
	{
	
	}
}
