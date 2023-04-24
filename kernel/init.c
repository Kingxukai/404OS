#include "../include/kernel.h"

extern void Init_trap();
extern void Init_uart();
extern void Init_timer();
extern void Init_page();
extern void Init_sched();

void Init()
{
	Init_page();
	Init_uart();
	Init_trap();
	Init_timer();
	Init_sched();
	/*other init*/
}
