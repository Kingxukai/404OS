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
<<<<<<< HEAD
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
=======
>>>>>>> b263a168e9b1161ebcebeb9fff679fda95062a44
	printf("task%d running\n",getpid());
	wait();
	printf("task%d running\n",getpid());
}
