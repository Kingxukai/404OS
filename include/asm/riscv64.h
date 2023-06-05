#ifndef _RISCV64_H__
#define _RISCV64_H__

#include "../type.h"
#include "../sched.h"

static inline void w_sscratch(reg64_t reg)
{
	asm volatile("csrw sscratch,%0"::"r"(reg));
}

static inline	reg64_t r_ssctrach()
{
	reg64_t reg;
	asm volatile("csrr %0,sscratch":"=r"(reg));
	return reg;
}

static inline	void w_sepc(reg64_t reg)
{
	asm volatile("csrw sepc,%0"::"r"(reg));
}

static inline void w_stvec(reg64_t reg)
{
	asm volatile("csrw stvec,%0"::"r"(reg));
}

static inline void w_sie(reg64_t reg)
{
	asm volatile("csrw sie,%0"::"r"(reg));
}

static inline	reg64_t r_sie()
{
	reg64_t reg;
	asm volatile("csrr %0,sie":"=r"(reg));
	return reg;
}

static inline void w_sstatus(reg64_t reg)
{
	asm volatile("csrw sstatus,%0"::"r"(reg));
}

static inline	reg64_t r_sstatus()
{
	reg64_t reg;
	asm volatile("csrr %0,sstatus":"=r"(reg));
	return reg;
}

static inline reg64_t r_tp()
{
	reg64_t reg;
	asm volatile("mv %0, tp" : "=r"(reg));
	return reg;
}

static inline reg64_t r_sip()
{
	reg64_t reg;
	asm volatile("csrr %0, sip" : "=r"(reg));
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

extern void timer_selfadd();

static inline void move_to_user_mode()
{
	asm volatile("csrw sepc,ra");
	timer_selfadd();
	#ifndef STACK_SIZE
	#define STACK_SIZE 1024*2
	#endif
	asm volatile("mv sp,%0"::"r"(&task_stack[0][STACK_SIZE-1]));
	asm volatile("sret");
}

#endif
