#include "../include/kernel.h"
static void show_hello();

void kernel_start(reg64_t hartid)
{
<<<<<<< HEAD
<<<<<<< Updated upstream
	if(!hardid)
=======
	if(!hartid)
>>>>>>> 872085f675df21c574d10487306b5c402149e374
	{
		show_hello();	// show hello 404
		printf("PLATFORM:%s\n",PLATFORM);
		printf("ARCH:%s\n",ARCH);
		printf("hart%d OK!!!\n",hartid);
		Init();				//Initial all
	}
	else printf("hart%d OK!!!\n",hartid);
	

=======
	printf("Loading...\n");
	show_hello();	// show hello 404
	Init();				//exceve task0
	printf("the bytes of void*is %d\n",sizeof(void*));
>>>>>>> Stashed changes
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
