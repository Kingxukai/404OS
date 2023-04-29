#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/riscv64.h"

void do_syscall(struct reg *context)										//syscall executing function
{
	reg64_t sys_num = context->a7;
	reg64_t ret_num = (*sys_call_table[sys_num])();				//call syscall_function
	context->a0 = ret_num;																//transmit ret_num
}

reg64_t sys_gethid()
{
	return r_mhartid();
}

reg64_t sys_getpid()
{
	return current->pid;
}
