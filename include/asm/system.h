#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#include "../type.h"
#include "riscv64.h"

#define NR_gethid 0
#define NR_getpid 1
#define NR_getppid 2
#define NR_fork 3
#define NR_execve 4
#define NR_exit	5
#define NR_waitpid 6
#define NR_shutdown 7

#define _syscall0(type,name) \
type name(void) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg0],a0":[arg0]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall1(type,name,type0,name0) \
type name(type0 name0) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg1],a0":[arg1]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall2(type,name,type0,name0,type1,name1) \
type name(type0 name0,type1 name1) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
	asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
	asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
	asm volatile("ecall"); \
	asm volatile("mv %[arg2],a0":[arg2]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall3(type,name,type0,name0,type1,name1,type2,name2) \
type name(type0 name0,type1 name1,type2 name2) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
  asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
  asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
  asm volatile("mv a2, %[arg2]" ::[arg2] "r" ((type2)name2)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg3],a0":[arg3]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall4(type,name,type0,name0,type1,name1,type2,name2,type3,name3) \
type name(type0 name0,type1 name1,type2 name2) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
  asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
  asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
  asm volatile("mv a2, %[arg2]" ::[arg2] "r" ((type2)name2)); \
  asm volatile("mv a3, %[arg3]" ::[arg3] "r" ((type3)name3)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg4],a0":[arg4]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall5(type,name,type0,name0,type1,name1,type2,name2,type3,name3,type4,name4) \
type name(type0 name0,type1 name1,type2 name2) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
  asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
  asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
  asm volatile("mv a2, %[arg2]" ::[arg2] "r" ((type2)name2)); \
  asm volatile("mv a3, %[arg3]" ::[arg3] "r" ((type3)name3)); \
  asm volatile("mv a4, %[arg4]" ::[arg4] "r" ((type4)name4)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg5],a0":[arg5]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#define _syscall6(type,name,type0,name0,type1,name1,type2,name2,type3,name3,type4,name4,type5,name5) \
type name(type0 name0,type1 name1,type2 name2) \
{ \
	asm volatile("li a7, %[_nr]" ::[_nr] "i" (NR_##name)); \
  asm volatile("mv a0, %[arg0]" ::[arg0] "r" ((type0)name0)); \
  asm volatile("mv a1, %[arg1]" ::[arg1] "r" ((type1)name1)); \
  asm volatile("mv a2, %[arg2]" ::[arg2] "r" ((type2)name2)); \
  asm volatile("mv a3, %[arg3]" ::[arg3] "r" ((type3)name3)); \
  asm volatile("mv a4, %[arg4]" ::[arg4] "r" ((type4)name4)); \
  asm volatile("mv a5, %[arg5]" ::[arg5] "r" ((type5)name5)); \
	asm volatile("ecall"); \
	reg64_t ret; \
	asm volatile("mv %[arg6],a0":[arg6]"=r" (ret)); \
	if(ret >= 0)return (type)ret; \
	return -1; \
}

#endif
