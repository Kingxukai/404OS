#include "../include/kernel.h"
#include "../include/asm/riscv64.h"
#include "../include/usr/unistd.h"
#include "../include/lock.h"
#include "../include/sbi.h"

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
extern void Init_page_table();
extern void Init_vm();

extern void _start();

struct spin_lock start_lock = {1};

void kernel_start(reg64_t hartid)
{
	if(!hartid)
	{
		show_hello();	// show hello 404
		printkRed("hart%d OK!!!\n",hartid);
		printkGreen("Loading...\n");
		printkYellow("\nInitial...\n");
		Init_page();
		Init_block_desc();
		Init_uart();
		Init_trap();
		Init_sched();
 		Init_plic();
 		Init_timer();
 		Init_buffer();
 		Init_virtio();
 		__sync_synchronize();
 		spin_unlock(&start_lock);
	}
	else 
	{
		setMode(1);
		uint64_t mask = 1<<0;
		sbi_send_ipi(&mask);
		spin_lock(&start_lock);
		printkRed("hart%d OK!!!\n",hartid);
		spin_unlock(&start_lock);
	}
 	//Init_page_table();
 	//Init_vm();

 	printkYellow("system initialed All!\n");
 	move_to_user_mode();
	if(!fork())Init();
	while(1){}
}

static void show_hello()
{
	printkGreen("\t                __________\n");
	printkGreen("\t|           |  |                                        ________ \n");
	printkGreen("\t|           |  |              |           |            /        \\ \n");
	printkGreen("\t|           |  |              |           |           /          \\ \n");
	printkGreen("\t|___________|  |__________    |           |          |            | \n");
	printkYellow("\t|           |  |              |           |          |            | \n");
	printkYellow("\t|           |  |              |           |          |            | \n");
	printkYellow("\t|           |  |              |           |           \\          / \n");
	printkYellow("\t|           |  |__________    |_________  |_________   \\________/  \n\n\n");
	
	printkWhite("\t\t\t            ________\n");
	printkWhite("\t\t\t|       |  |        |  |       |\n");
	printkWhite("\t\t\t|       |  |        |  |       |\n");
	printkWhite("\t\t\t|_______|  |        |  |_______|\n");
	printkRed("\t\t\t        |  |        |          | \n");
	printkRed("\t\t\t        |  |        |          | \n");
	printkRed("\t\t\t        |  |________|          | \n");
}
