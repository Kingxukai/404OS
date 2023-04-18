#include "timer.h"
void Init_timer()
{
	w_mstatus(r_mstatus() | 1 << 3);
	
	w_mie(r_mie() | 1 << 7);

}

void timer_interrupt_hander()
{
	current->time++;
	if(_current)
	{
		timer_selfadd();
		if(--(current->counter) > 0)
		{
			return;
		}
		task_exit();
	}
	else return;
	schedule();
}

void timer_selfadd()
{
	uint64_t hart = r_mhartid();
	*(uint64_t*)CLIENT_MTIMERCMP(hart) = *(uint64_t*)CLIENT_MTIMER + CLOCK_PER_SECOND;
}
