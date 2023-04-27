#include "../include/timer.h"
#include "../include/sched.h"
#include "../include/trap.h"

volatile uint64_t jiffies = 0;

void timer_selfadd()
{
	jiffies++;
	uint64_t hart = r_mhartid();
	*(uint64_t*)CLIENT_MTIMERCMP(hart) = *(uint64_t*)CLIENT_MTIMER + CLOCK_PIECE;
}

void Init_timer()
{
	printf("Initial timer...\n");
	w_mstatus(r_mstatus() | EA);
	
	w_mie(r_mie() | MTIE);
	
	printf("Initialed All!\n");
}

void timer_interrupt_handler()
{
	current->time++;
	timer_selfadd();
	if(current->pid) 
	{
		if(--(current->counter) > 0)
		{
			timer_selfadd();
			return;
		}
	}
	schedule();
}

