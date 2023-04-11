#include "../../include/sched.h"

//2023-04-02 12:45:46 

struct PCB *task_struct[MAX_TASK] = {&INIT_TASK,};
struct PCB *current = &INIT_TASK;
u16 task_stack[MAX_TASK][STACK_SIEZE];

void schedule()
{
	struct PCB ** p =&task_struct[MAX_TASK];
	struct PCB *next;

	u16 MAX_priority = LOW;
	int i = MAX_TASK;
	while(--i)
	{
		if(!(*--p))continue;
		if((*p)->priority > current->priority && (*p)->pirority >= MAX_priority)
		{
			next = *p;
			MAX_priority = (*p)->priority;
		}
	}
	current = next;
	switch_to(&(next->context));
}

void init_sched()
{
	w_mscratch(0);
}
