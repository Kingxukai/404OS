#ifndef _TRAP_H__
#define _TRAP_H__

#include "../include/platform.h"

static inline w_mscratch(reg64 reg)							
{
	asm volatile("csrw mscratch, %0" : : "r" (reg));
}

static inline r_mscratch(reg64 reg)
{
	asm volatile("csrr %0,mscratch" : "=r" (reg));
}

static inline w_mepc(reg64 reg)							
{
	asm volatile("csrw mepc, %0" : : "r" (reg));
}

static inline r_mepc(reg64 reg)
{
	asm volatile("csrr %0,mepc" : "=r" (reg));
}

static inline w_mtevc(reg64 reg)							
{
	asm volatile("csrw mtevc, %0" : : "r" (reg));
}

#endif
