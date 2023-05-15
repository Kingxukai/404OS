#ifndef _RISCV64_H__
#define _RISCV64_H__

#include "type.h"
#include "sched.h"
#define STACK_SIZE 1024

static inline reg64_t r_mhartid()
{
	reg64_t reg;
	asm volatile("csrr %0, mhartid" : "=r" (reg) );
	return reg;
}

static inline void w_mscratch(reg64_t reg)
{
	asm volatile("csrw mscratch,%0"::"r"(reg));
}

static inline	reg64_t r_msctrach()
{
	reg64_t reg;
	asm volatile("csrr %0,mscratch":"=r"(reg));
	return reg;
}

static inline	void w_mepc(reg64_t reg)
{
	asm volatile("csrw mepc,%0"::"r"(reg));
}

static inline void w_mtvec(reg64_t reg)
{
	asm volatile("csrw mtvec,%0"::"r"(reg));
}

static inline void w_mie(reg64_t reg)
{
	asm volatile("csrw mie,%0"::"r"(reg));
}

static inline	reg64_t r_mie()
{
	reg64_t reg;
	asm volatile("csrr %0,mie":"=r"(reg));
	return reg;
}

static inline void w_mstatus(reg64_t reg)
{
	asm volatile("csrw mstatus,%0"::"r"(reg));
}

static inline	reg64_t r_mstatus()
{
	reg64_t reg;
	asm volatile("csrr %0,mstatus":"=r"(reg));
	return reg;
}

static inline reg64_t r_tp()
{
	reg64_t reg;
	asm volatile("mv %0, tp" : "=r"(reg));
	return reg;
}

static inline reg64_t r_mip()
{
	reg64_t reg;
	asm volatile("csrr %0, mip" : "=r"(reg));
	return reg;
}

static inline void w_a0(reg64_t reg)
{
	asm volatile("li a0,%0"::"r"(reg));
}

static inline void w_a1(reg64_t reg)
{
	asm volatile("li a1,%0"::"r"(reg));
}

static inline void w_a2(reg64_t reg)
{
	asm volatile("li a2,%0"::"r"(reg));
}

static inline void w_a3(reg64_t reg)
{
	asm volatile("li a3,%0"::"r"(reg));
}

static inline void w_a4(reg64_t reg)
{
	asm volatile("li a4,%0"::"r"(reg));
}

static inline void w_a5(reg64_t reg)
{
	asm volatile("li a5,%0"::"r"(reg));
}

static inline void w_a6(reg64_t reg)
{
	asm volatile("li a6,%0"::"r"(reg));
}

static inline void w_a7(reg64_t reg)
{
	asm volatile("li a7,%0"::"r"(reg));
}

static inline void asm_ecall()
{
	asm volatile("ecall");
}

static inline void asm_ret()
{
	asm volatile("ret");
}

static inline void move_to_user_mode()
{
	asm volatile("csrw mepc,ra");
	asm volatile("mv sp,%0"::"r"((reg64_t)&task_stack[0][STACK_SIZE - 1]));
	asm volatile("mret");
}

#endif
