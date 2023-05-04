#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/riscv64.h"

void do_syscall(struct reg *context)										//syscall executing function
{
	reg64_t sys_num = context->a7;
	sys_func fn;
	fn = (sys_func)sys_call_table[sys_num];
	context->a0 = (*fn)(context->a0,context->a1,context->a2,context->a3,context->a4,context->a5);
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

int sys_execve(const char *filepath,char * const * argv,char * const * envp)
{
	struct task_struct *p = current;
	if(filepath)
	{
		p->context.ra = (reg64_t)filepath;
		p->context.sp = (reg64_t)&task_stack[p->pid][STACK_SIZE-1];	
		p->context.gp = 0;
		p->context.tp = 0;
		p->context.t0 = 0;
		p->context.t1 = 0;
		p->context.t2 = 0;
		p->context.s0 = current->context.s0;
		p->context.s1 = 0;
		p->context.a0 = 0;										
		p->context.a1 = 0;
		p->context.a2 = 0;
		p->context.a3 = 0;
		p->context.a4 = 0;
		p->context.a5 = 0;
		p->context.a6 = 0;
		p->context.a7 = 0;
		p->context.s2 = 0;
		p->context.s3 = 0;
		p->context.s4 = 0;
		p->context.s5 = 0;
		p->context.s6 = 0;
		p->context.s7 = 0;
		p->context.s8 = 0;
		p->context.s9 = 0;
		p->context.s10 = 0;
		p->context.s11 = 0;
		p->context.t3 = 0;
		p->context.t4 = 0;
		p->context.t5 = 0;
		p->context.t6 = 0;
		p->context.epc = (reg64_t)filepath;
		return 0;
	}
	else return -1;
}

pid_t sys_exit()
{
	return do_exit();
}

void* sys_malloc()
{
	void *nil = NULL;
	return nil;
}
