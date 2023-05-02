#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/riscv64.h"

void do_syscall(struct reg *context)										//syscall executing function
{
	reg64_t sys_num = context->a7;
	sys_func fn;
	fn = (sys_func)sys_call_table[sys_num];
	context->a0 = (*fn)(context->a0,context->a1,context->a2);
}

uint64_t sys_gethid()	
{
	return r_mhartid();
}

pid_t sys_getpid()
{
	return current->pid;
}

pid_t sys_getppid()
{
	return current->father_pid;
}

pid_t sys_fork()
{
	if( find_new_pid() >= MAX_TASK )
	{	
		panic("No free task_id to create!\n");
	}
	
	return copy_process();
}

void* sys_malloc()
{
	void *nil = NULL;
	return nil;
}
