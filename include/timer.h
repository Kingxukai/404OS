#ifndef _TIMER_H__
#define _TIMER_H__

#include "type.h"

#define FREQUNCE (1000 * 1000 * 1000)					//1GHZ
#define CLOCK_PIECE (FREQUNCE/(1000 * 10))			//1GHZ / (1000 * 10) = 100us

void Init_timer();
void timer_interrupt_handler();

volatile uint64_t jiffies;

#endif
