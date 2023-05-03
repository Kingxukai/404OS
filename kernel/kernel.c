#include "../include/kernel.h"
static void show_hello();

void kernel_start(reg64_t hartid)
{
	if(!hartid)
	{
		show_hello();	// show hello 404
		printf("PLATFORM:%s\n",PLATFORM);
		printf("ARCH:%s\n",ARCH);
		printf("hard%d OK!!!\n",hartid);
		Init();				//Initial all
	}
	else printf("hard%d OK!!!\n",hartid);
	

	schedule();		//schedule to switch from machine mode to user mode and  run task0  in free time
	while(1)
	{
		
	}
	panic("unexpected executing step\n");
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
	
	printf("\t\t\t            ________\n");
	printf("\t\t\t|       |  |        |  |       |\n");
	printf("\t\t\t|       |  |        |  |       |\n");
	printf("\t\t\t|_______|  |        |  |_______|\n");
	printf("\t\t\t        |  |        |          | \n");
	printf("\t\t\t        |  |        |          | \n");
	printf("\t\t\t        |  |________|          | \n");
}
