#include "../include/kernel.h"

extern void Init_trap();
extern void Init_uart();
extern void Init_timer();

void Init()
{
	Init_uart();
	Init_trap();
	Init_timer();
	Init_sched();
	/*other init*/
}
