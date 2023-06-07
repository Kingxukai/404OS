#include "../include/sys.h"
#include "../include/sched.h"
#include "../include/asm/riscv64.h"
#include "../include/type.h"
#include "../include/errno.h"
#include "../include/usr/lib.h"
#include "../include/usr/unistd.h"
#include "../include/platform.h"

void do_syscall(struct reg *context)										//syscall executing function
{
	reg64_t sys_num = context->a7;
	sys_func fn;
	fn = (sys_func)sys_call_table[sys_num];
	context->a0 = (*fn)(context->a0,context->a1,context->a2,context->a3,context->a4,context->a5);
}

uint64_t sys_gethid()	
{
	return r_tp();
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
	return do_execve(filepath,argv,envp);
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
				if(pid != (*p)->pid)
					continue;
			}
			else if(pid == 0)
				continue;
			else if(pid != -1)
				continue;
				
			if((*p)->state == TASK_ZOMBINE)
			{
				current->time += (*p)->time;
				*stat_addr = (*p)->exit_code;
				pid = (*p)->pid;
				release(*p);
				return pid;
			}
			else if((*p)->state == TASK_STOP)
			{
				return (*p)->pid;
			}
			else flag = 1;
		}
		if(flag)
		{
			current->state = TASK_WAIT;
			current->in_Queue = 0;
			
			schedule();
			
			if(!(current->signal &= (~SIG_CHLD)))
				goto repeat;
			else
				{
					return -EINTR;
				}
		}
	return -ECHILD;
}

int sys_shutdown()
{
	ADDR(SYS_CTL_ADDR) = SYS_CTL(SYS_PASS);
}
