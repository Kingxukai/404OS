#include "../include/system.h"
#include "../include/printf.h"

void task1()
{
	printf("task%d running\n",getpid());
	exit();
}

void task2()
{
	while(1)
	{
		printf("task%d running\n",getpid());
	}
}

void task0()
{
	printf("malooc\n");
	printf("task0 create\n");
	printf("task0 running\n");
	pid_t pid1,pid2;
	if((pid1 = fork()) == 0)
	{
		execve(task1,NULL,NULL);
	}
	else if((pid2 = fork()) == 0)
	{
		execve(task2,NULL,NULL);
	}
	else
	{
		printf("here is father task\n");
		printf("task%d create\n",pid1);
		printf("task%d create\n",pid2);
	}
	printf("task%d running\n",getpid());

	while(1)
	{
		//printf("task%d running\n",getpid());
	}
}
