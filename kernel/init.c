#include "../include/kernel.h"

extern void Init_trap();
extern void Init_uart();
extern void Init_timer();
extern void Init_page();
extern void Init_sched();
extern void Init_plic();

void Init()
{
	printf("\nInitial...\n");
	Init_page();
	Init_uart();
	Init_trap();
	Init_plic();
	Init_sched();
	Init_timer();
	/*other init*/
}
