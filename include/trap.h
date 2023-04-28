#ifndef _TRAP_H__
#define _TRAP_H__

#include "platform.h"
#include "type.h"

void Init_trap();
uint64_t claim();
void complete(uint64_t irq);
extern void trap_vector();

#define EA (1<<3)				//control all interrupt
#define MTIE (1<<7)			//control machine timer interrupt
#define MEIE (1<<11)		//control machine externel interrupt

#endif
