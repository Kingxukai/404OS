#include "../include/kernel.h"
#include "../include/asm/riscv64.h"
static void show_hello();

extern void Init_trap();
extern void Init_uart();
extern void Init_timer();
extern void Init_page();
extern void Init_sched();
extern void Init_plic();
extern void Init_block_desc();
extern void Init_buffer();
extern void Init_virtio();

void kernel_start(reg64_t hartid)
{
	if(!hartid)

	{
		show_hello();	// show hello 404
		printk("PLATFORM:%s\n",PLATFORM);
		printk("ARCH:%s\n",ARCH);
		printk("hart%d OK!!!\n",hartid);
	}
	else printk("hart%d OK!!!\n",hartid);
	
	printk("Loading...\n");
	printk("\nInitial...\n");
	Init_page();
	Init_block_desc();
	Init_uart();
	Init_trap();
	Init_sched();
 	Init_plic();
 	Init_buffer();
 	Init_virtio();
 	Init_timer();
 	printk("Initialed All!\n");
 	move_to_user_mode();
	if(!fork())Init();
	while(1){}
}

static void show_hello()
{
	printk("\t                __________\n");
	printk("\t|           |  |                                        ________ \n");
	printk("\t|           |  |              |           |            /        \\ \n");
	printk("\t|           |  |              |           |           /          \\ \n");
	printk("\t|___________|  |__________    |           |          |            | \n");
	printk("\t|           |  |              |           |          |            | \n");
	printk("\t|           |  |              |           |          |            | \n");
	printk("\t|           |  |              |           |           \\          / \n");
	printk("\t|           |  |__________    |_________  |_________   \\________/  \n\n\n");
	
	printk("\t\t\t            ________\n");
	printk("\t\t\t|       |  |        |  |       |\n");
	printk("\t\t\t|       |  |        |  |       |\n");
	printk("\t\t\t|_______|  |        |  |_______|\n");
	printk("\t\t\t        |  |        |          | \n");
	printk("\t\t\t        |  |        |          | \n");
	printk("\t\t\t        |  |________|          | \n");
}
