#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/riscv64.h"

int do_syscall(struct reg *context)
{
	int sys_num = context->a7;
	int ret_num = *sys_call_table[sys_num];				//call syscall_function
	return ret_num;
}

int sys_gethid()
{
	return r_mhartid();
}
