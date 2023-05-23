#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/asm/riscv64.h"
#include "../include/type.h"
#include "../include/errno.h"
#include "../include/usr/lib.h"
#include "../include/usr/unistd.h"

reg64_t ret_from_sys_call();

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
	if( find_new_id() >= MAX_TASK )
	{	
		panic("No free PCB_id to request!\n");
	}
	
	return copy_process();
}

int sys_execve(const char *filepath,char * const * argv,char * const * envp)
{
	struct task_struct *p = current;
	if(argv[0])
	{
		p->context.ra = (reg64_t)ret_from_sys_call;
		p->context.sp = (reg64_t)&task_stack[p->pcb_id][STACK_SIZE-1];	
		p->context.gp = 0;
		p->context.tp = 0;
		p->context.t0 = 0;
		p->context.t1 = 0;
		p->context.t2 = 0;
		p->context.s0 = 0;
		p->context.s1 = 0;
		p->context.a0 = (reg64_t)(sizeof(argv) / sizeof(char*));	//transfer the arg to filepath/process and sizeof(argv) is argc
		p->context.a1 = (reg64_t)argv;
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
		p->context.epc = (reg64_t)argv[0];
		p->context.temp = (reg64_t)exit;	//make it over while exit current process
		switch_to(0, &(p->context));
	}
	else
		return -1;
}

pid_t sys_exit(int error_code)
{
	return do_exit(error_code);
}

pid_t sys_waitpid(pid_t pid,uint64_t* stat_addr,int options)
{
	bool flag;
	struct task_struct **p;
	int i;
	repeat:
		p = &TASK[MAX_TASK];
		i = MAX_TASK;
		flag = 0;
		while(--i)
		{
			if(!*--p || *p == current)continue;
			if((*p)->father_pid != current->pid)continue;
			if(pid > 0)
			{
				if(pid != (*p)->pid)continue;
				if((*p)->state == TASK_ZOMBINE)
				{
					current->time += (*p)->time;
					release(*p);
				}
				else flag = 1;
			}
		}
		if(flag)
		{
			current->state = TASK_WAIT;
			current->in_Queue = 0;
			
			struct reg* context = (struct reg*)malloc(sizeof(struct reg));
			memcpy((reg8_t *)&(current->context),(reg8_t *)context,sizeof(struct reg));
			schedule();
			memcpy((reg8_t *)context,(reg8_t *)&(current->context),sizeof(struct reg));
			free(context);
			
			if(!(current->signal &= (~SIG_CHLD)))
				goto repeat;
			else
				{
					return -EINTR;
				}
		}
	return -ECHILD;
}
