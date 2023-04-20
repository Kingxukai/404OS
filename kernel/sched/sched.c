#include "../../include/sched.h"

//2023-04-02 12:45:46 

struct task_struct *task_struct[MAX_TASK] = {&INIT_TASK,};
struct task_struct *current = &INIT_TASK;
uint16_t task_stack[MAX_TASK][STACK_SIEZ];

void schedule()
{
	struct task_struct ** p =&task_struct[MAX_TASK];
	struct task_struct *next;

	uint16_t MAX_priority = LOW;
	int i = MAX_TASK;
	while(--i)
	{
		if(!(*--p))continue;
		if((*p)->priority > current->priority && (*p)->priority >= MAX_priority)
		{
			next = *p;
			MAX_priority = (*p)->priority;
		}
	}
	current = next;
	timer_selfadd();
	switch_to(&(next->context));
}

void Init_sched()
{
	w_mscratch(0);
	
}
