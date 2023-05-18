#include "../include/unistd.h"
#include "../include/printf.h"
#include "../include/lib.h"

void task3()
{
	printf("task%d running\n",getpid());
	printf("my father is %d\n",getppid());
	exit();
}

void task4()
{
	int t = 5;
	printf("my father is %d\n",getppid());
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task5()
{
	printf("task%d running\n",getpid());
	printf("my father is %d\n",getppid());
	printf("task%d running\n",getpid());
	while(1)
	{
	
	}
}

void task2()
{
	printf("task%d is running\n",getpid());
	pid_t pid3,pid4,pid5,n = 0;
	if((pid3 = fork()) == 0)
	{
		execve(task3,NULL,NULL);
	}
	else if((pid4 = fork()) == 0)
	{
		execve(task4,NULL,NULL);
	}
	else if((pid5 = fork()) == 0)
	{
		execve(task5,NULL,NULL);
	}
	else
	{
		printf("task%d has created\n",pid3);
		printf("task%d has created\n",pid4);
		printf("task%d has created\n",pid5);
		waitpid(pid4,NULL,0);
		printf("here is father process\n");
	}
	while(1)
	{
	}
}
