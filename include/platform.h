#ifndef _PLATFORM_H__
#define _PLATFORM_H__

#define CPU_NUM 2

typedef unsigned char u8;			//data 8bit
typedef unsigned short u16;		//data 16bit
typedef unsigned int u32;			//data 32bit
typedef unsigned long u64;		//data 64bit

typedef reg8 u8								//register 8bit
typedef reg16 u16							//register 16bit
typedef reg32 u32							//register 32bit
typedef reg64 u64						 //register 64bit

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
