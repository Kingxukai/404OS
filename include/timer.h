#ifndef _TIMER_H__
#define _TIMER_H__

#include "type.h"

#define FREQUNCE (1000 * 1000 * 1000)					//1GHZ
#define CLOCK_PIECE (FREQUNCE/1000)			//1GHZ / 1000 = 1ms

void Init_timer();
void timer_interrupt_handler();

volatile uint64_t jiffies;

struct timer_list
{
	uint64_t jiffies;
	void (*fn)();
	struct timer_list *next;
}*timer_head = NULL;

#endif
