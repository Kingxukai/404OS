#include "../include/system.h"
#include "../include/printf.h"

void task0()
{
	printf("task0 create\n");
	printf("task0 running\n");
	int pid1,pid2;
	if((pid1 = fork()) == 0)
	{
		printf("task%d running\n",getpid());
		printf("my father pid:%d\n",getppid());
	}
	else if((pid2 = fork()) == 0)
	{
		printf("task%d running\n",getpid());
		printf("my father pid:%d\n",getppid());
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
