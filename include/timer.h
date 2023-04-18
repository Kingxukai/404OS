#ifndef _TIMER_H__
#define _TIMER_H__

#define CLOCK_PER_SEC 1000 * 100		//CLOCK=10us
static uint64_t jiffies = 0;

void Init_timer();
void timer_interrupt_hander();
void timer_selfadd();

#endif
