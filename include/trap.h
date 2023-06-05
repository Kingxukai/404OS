#ifndef _TRAP_H__
#define _TRAP_H__

#include "platform.h"
#include "type.h"

void Init_trap();
uint64_t claim();
void complete(uint64_t irq);
extern void trap_vector();

#define EA (1<<1)				//control all interrupt
#define STIE (1<<5)			//control machine timer interrupt
#define SEIE (1<<9)		//control machine externel interrupt

#define U_MODE 0
#define S_MODE 1	
#define M_MODE 3

#endif
