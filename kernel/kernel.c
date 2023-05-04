#include "../include/kernel.h"
static void show_hello();

extern void Init_trap();
extern void Init_uart();
extern void Init_timer();
extern void Init_page();
extern void Init_sched();
extern void Init_plic();
extern void Init_block_desc();

void kernel_start(reg64_t hartid)
{

	if(!hartid)

	{
		show_hello();	// show hello 404
		printf("PLATFORM:%s\n",PLATFORM);
		printf("ARCH:%s\n",ARCH);
		printf("hart%d OK!!!\n",hartid);
	}
	else printf("hart%d OK!!!\n",hartid);
	
	printf("Loading...\n");
	printf("\nInitial...\n");
	Init_page();
	Init_block_desc();
	Init_uart();
	Init_trap();
	Init_sched();
	Init_timer();
 	Init_plic();
	printf("Initialed All!\n");
	schedule();		//schedule to switch from machine mode to user mode and  run init(task0)
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
