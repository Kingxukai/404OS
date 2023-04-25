#include "../include/kernel.h"
static void show_hello();

void kernel_start()
{
	printf("Loading...\n");
	show_hello();	// show hello 404
	Init();				//exceve task0
	schedule();		//schedule to run task0 in free time
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
