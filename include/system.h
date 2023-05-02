#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#include "type.h"
#include "riscv64.h"

uint64_t gethid();	//0
pid_t getpid();	//1
pid_t getppid();	//2
pid_t fork(); //3
void* malloc();	//4

#define NR_gethid 0
#define NR_getpid 1
#define NR_getppid 2
#define NR_fork 3
#define NR_malloc 4

#define _syscall0(type,name) \
type name(void) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("ecall"); \
	asm volatile("ret"); \
}

#define _syscall1(type,name,type0,name0) \
type name(type0 name0) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
	asm volatile("ecall"); \
	asm volatile("ret"); \
}

#define _syscall2(type,name,type0,name0,type1,name1) \
type name(type0 name0,type1 name1) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
	asm volatile("mv a0, %[arg1]" ::[arg1] "r" ((type1)name1)); \
	asm volatile("ecall"); \
	asm volatile("ret"); \
}

#define _syscall3(type,name,type0,name0,type1,name1,type2,name2) \
type name(type0 name0,type1 name1,type2 name2) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
  asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
  asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
  asm volatile("mv a2, %[arg2]" ::[arg2] "r" ((type2)name2)); \
	asm volatile("ecall"); \
	asm volatile("ret"); \
}

#endif
