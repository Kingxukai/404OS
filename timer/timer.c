#include "../include/timer.h"
#include "../include/sched.h"
#include "../include/trap.h"

void timer_selfadd()
{
	uint64_t hart = r_mhartid();
	*(uint64_t*)CLIENT_MTIMERCMP(hart) = *(uint64_t*)CLIENT_MTIMER + CLOCK_PER_SEC;
}

void Init_timer()
{
	printf("Initial timer...\n");
	w_mstatus(r_mstatus() | 1 << 3);
	
	w_mie(r_mie() | 1 << 7);
	
	timer_selfadd();
	printf("Initial All!\n");
}

void timer_interrupt_handler()
{
	current->time++;
	timer_selfadd();
	if(current->pid)
	{
		if(--(current->counter) > 0)
		{
			return;
		}
	}
	schedule();
}

