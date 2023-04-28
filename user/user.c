#include "../include/system.h"

void task0()
{
	printf("task0 create\n");
	printf("task0 running\n");
	int pid1,pid2;
	if(pid1 = copy_process())printf("task%d create\n",pid1);
	if(pid2 = copy_process())printf("task%d create\n",pid2);
	printf("return from system_call\n");
	int id = gethid();
	printf("current hartid:%d\n",id);
	while(1)
	{
		//printf("task running\n");
	}
}
