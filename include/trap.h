#ifndef _TRAP_H__
#define _TRAP_H__

#include "platform.h"

trap_Init();
uint64_t claim();
void complete(uint64_t irq);

static inline reg64 r_mhartid()
{
	reg64 reg;
	asm volatile("csrr %0, mhartid" : "=r" (reg) );
	return reg;
}

static inline void w_mscratch(reg64 reg)
{
	asm volatile("csrw mscratch,%0"::"r"(reg));
}

static inline	reg64 r_msctrach()
{
	reg64 reg;
	asm volatile("csrr %0,mscratch":"=r"(reg));
	return reg;
}

static inline	void w_mepc(reg64 reg)
{
	asm volatile("csrw mepc,%0"::"r"(reg));
}

static inline void w_mtvec(reg64 reg)
{
	asm volatile("csrw mtvec,%0"::"r"(reg));
}

static inline void w_mie(reg64 reg)
{
	asm volatile("csrw mie,%0"::"r"(reg));
}

static inline	reg64 r_mie()
{
	reg64 reg;
	asm volatile("csrr %0,mie":"=r"(reg));
	return reg;
}

static inline void w_mstatus(reg64 reg)
{
	asm volatile("csrw mstatus,%0"::"r"(reg));
}

static inline	reg64 r_mstatus()
{
	reg64 reg;
	asm volatile("csrr %0,mstatus":"=r"(reg));
	return reg;
}

static inline reg64 r_tp()
{
	reg64 reg;
	asm volatile("mv %0, tp" : "=r"(reg));
	return reg;
}

static inline reg64 r_mip()
{
	reg64 reg;
	asm volatile("csrr %0, mip" : "=r"(reg));
	return reg;
}

#endif
