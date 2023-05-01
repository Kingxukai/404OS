#include "../../include/sched.h"
#include "../../include/kernel.h"
#include "../../include/timer.h"

uint16_t task_stack[MAX_TASK][STACK_SIZE];			//each task occupy 1024*2B stack size

extern struct task_struct *current;

static pid_t find_new_pid()
{
	pid_t i = 0;
	struct task_struct ** p = &TASK[0];
	while(++i<MAX_TASK)
	{
		if(*++p)continue;
		return i;
	}
	return MAX_TASK;
}

pid_t copy_process()
{
	pid_t new_id = 0;
	if( (new_id = find_new_pid()) >= MAX_TASK )
	{	
		panic("No free task_id to create!\n");
	}
	else
	{
		struct task_struct *p = (struct task_struct *)page_alloc(1);
		if(!p) panic("something wrong in page alloc,please check\n");																//something wrong in page alloc
		TASK[new_id] = p;
		
		p->pid = new_id;
		p->father_pid = current->pid;
		p->state = TASK_READY;
		p->start_time = jiffies;
		p->time = 0;
		p->priority = current->priority;
		p->counter = p->priority;
		p->order = 0;
		p->in_Queue = 0;

		p->context.ra = current->context.ra;
		p->context.sp = (reg64_t)task_stack[p->pid][STACK_SIZE-1];
		p->context.gp = current->context.gp;
		p->context.tp = current->context.tp;
		p->context.t0 = current->context.t0;
		p->context.t1 = current->context.t1;
		p->context.t2 = current->context.t2;
		p->context.s0 = current->context.s0;
		p->context.s1 = current->context.s1;
		p->context.a0 = current->context.a0;
		p->context.a1 = current->context.a1;
		p->context.a2 = current->context.a2;
		p->context.a3 = current->context.a3;
		p->context.a4 = current->context.a4;
		p->context.a5 = current->context.a5;
		p->context.a6 = current->context.a6;
		p->context.a7 = current->context.a7;
		p->context.s2 = current->context.s2;
		p->context.s3 = current->context.s3;
		p->context.s4 = current->context.s4;
		p->context.s5 = current->context.s5;
		p->context.s6 = current->context.s6;
		p->context.s7 = current->context.s7;
		p->context.s8 = current->context.s8;
		p->context.s9 = current->context.s9;
		p->context.s10 = current->context.s10;
		p->context.s11 = current->context.s11;
		p->context.t3 = current->context.t3;
		p->context.t4 = current->context.t4;
		p->context.t5 = current->context.t5;
		p->context.t6 = current->context.t6;
		p->context.epc = current->context.epc + 4;
						
		return p->pid;
	}
}

/*int execve()
{
	
}*/
