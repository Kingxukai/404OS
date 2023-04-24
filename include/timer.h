#ifndef _TIMER_H__
#define _TIMER_H__

#include "type.h"

#define CLOCK_PER_SEC 1000 * 100		//CLOCK=10us

void Init_timer();
void timer_interrupt_hanlder();

#endif
