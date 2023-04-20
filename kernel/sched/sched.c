#include "../../include/sched.h"

//2023-04-02 12:45:46 

void switch_to(struct reg* next);

struct task_struct *TASK[MAX_TASK] = {&INIT_TASK,};
struct task_struct *current = &INIT_TASK;

void schedule()
{
	struct task_struct ** p =&TASK[MAX_TASK];
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
