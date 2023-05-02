#include "../include/kernel.h"
static void show_hello();

void kernel_start(reg64_t hardid)
{
	printf("Loading hart%d...\n",hardid);
	if(!hardid)
	{
		show_hello();	// show hello 404
		Init();				//Initial all
	}
	printf("hard%d OK!!!\n",hardid);
	schedule();		//schedule to switch from machine mode to user mode and  run task0  in free time
	while(1)
	{
		
	}
}

static void show_hello()
{
	printf("\t                __________\n");
	printf("\t|           |  |                                        ________ \n");
	printf("\t|           |  |              |           |            /        \\ \n");
	printf("\t|           |  |              |           |           /          \\ \n");
	printf("\t|___________|  |__________    |           |          |            | \n");
	printf("\t|           |  |              |           |          |            | \n");
	printf("\t|           |  |              |           |          |            | \n");
	printf("\t|           |  |              |           |           \\          / \n");
	printf("\t|           |  |__________    |_________  |_________   \\________/  \n\n\n");
	
	printf("\t\t\t            ________          \n");
	printf("\t\t\t|       |  |        |  |       |\n");
	printf("\t\t\t|       |  |        |  |       |\n");
	printf("\t\t\t|_______|  |        |  |_______|\n");
	printf("\t\t\t        |  |        |          | \n");
	printf("\t\t\t        |  |        |          | \n");
	printf("\t\t\t        |  |________|          | \n");
}
