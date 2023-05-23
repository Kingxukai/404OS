#include "../include/usr/unistd.h"
#include "../include/usr/printf.h"
#include "../include/usr/lib.h"

int task3(int argc,char* argv[])
{
	printf("task%d running\n",getpid());
	printf("argc:%d\n",argc);
	for(int i = 0;i < argc;i++)
	{
		printf("argv%d:%x\n",i,argv[i]);
	}
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
		char *argv[]={task3};   
		char *envp[]={"PATH=/bin", NULL};   
		execve("/usr/temp", argv, envp);
	}
	else if((pid4 = fork()) == 0)
	{
		char *argv[]={task4};
		execve(NULL,argv,NULL);
	}
	else if((pid5 = fork()) == 0)
	{
		char *argv[]={task5};
		execve(NULL,argv,NULL);
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

