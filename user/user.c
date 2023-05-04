#include "../include/unistd.h"
#include "../include/printf.h"

void task1()
{
	printf("task%d running\n",getpid());
	exit();
}

void task2()
{
	int t = 5;
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	exit();
}

void task3()
{
	printf("task%d running\n",getpid());
	wait();
	printf("task%d running\n",getpid());
}
