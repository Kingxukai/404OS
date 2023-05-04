#include "../include/kernel.h"
#include "../include/unistd.h"

extern void task1();
extern void task2();
extern void task3();

void Init()
{
	/*other init*/
	pid_t pid1,pid2,pid3;
	if((pid1 = fork()) == 0)
	{
		execve(task1,NULL,NULL);
	}
	else if((pid2 = fork()) == 0)
	{
		execve(task2,NULL,NULL);
	}
	else if((pid3 = fork()) == 0)
	{
		execve(task3,NULL,NULL);
	}
	else
	{
		printf("task%d has created\n",pid1);
		printf("task%d has created\n",pid2);
		printf("task%d has created\n",pid3);
		printf("here is father process\n");

	}
	while(1)
	{
		
	}
	panic("unexpected step?!\n");
}
