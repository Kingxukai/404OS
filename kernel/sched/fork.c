#include "../../include/sched.h"
#include "../../include/kernel.h"
#include "../../include/timer.h"

uint16_t task_stack[MAX_TASK][STACK_SIZE];

extern struct task_struct *current;

uint16_t get_newpid()
{
	uint16_t i = 0;
	struct task_struct ** p = &TASK[0];
	while(++i<MAX_TASK)
	{
		if(!(*++p))continue;
		return i;
	}
	return MAX_TASK;
}

int copy_process()
{
	uint16_t new_id = 0;
	if( (new_id = get_newpid()) >= MAX_TASK )
	{	
		panic("No free task_id to create!\n");
	}
	else
	{
		struct task_struct *p = (struct task_struct *)page_alloc(sizeof(struct task_struct));
		if(!p) return -1;																//something wrong in page alloc
		TASK[new_id] = p;
		
		p = current;
		p->pid = new_id;
		p->father_id = current->pid;
		p->state = TASK_READY;
		p->start_time = jiffies;
		p->time = 0;
		p->priority = current->priority;
		p->counter = p->priority;
		p->context.sp = (reg64_t)task_stack[p->pid];
	}
	return 0;
}

/*int execve()
{
	
}*/

void task0()
{
	Init_timer();
	printf("task0 create\n");
	printf("task0 running\n");
	while(1)
	{
		
	}
}
