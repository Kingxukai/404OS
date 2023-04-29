#include "../include/system.h"
#include "../include/printf.h"

void task0()
{
	printf("task0 create\n");
	printf("task0 running\n");
	int pid1,pid2;
	if(pid1 = fork())printf("task%d create\n",pid1);
	if(pid2 = fork())printf("task%d create\n",pid2);
	while(1)
	{
		printf("current hartid:%d\n",gethid());
		printf("task%d running\n",getpid());
		printf("my father pid:%d\n",getppid());
	}
}
