#include "../include/unistd.h"
#include "../include/printf.h"
#include "../include/lib.h"

int task3(char* argv,char* envp)
{
	printf("task%d running\n",getpid());
	printf("argv:%s\nenvp:%s\n",argv,envp);
	printf("my father is %d\n",getppid());
	return 0;
}

int task4()
{
	int t = 5;
	printf("my father is %d\n",getppid());
	while(t--)
	{
		printf("task%d running\n",getpid());
	}
	return 0;
}

int task5()
{
	printf("task%d running\n",getpid());
	printf("my father is %d\n",getppid());
	printf("task%d running\n",getpid());
	while(1)
	{
		
	}
	return 0;
}

int task2()
{
	printf("task%d is running\n",getpid());
	pid_t pid3,pid4,pid5;
	if((pid3 = fork()) == 0)
	{
		execve(task3,"666","/usr/task3");
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
	return 0;
}

