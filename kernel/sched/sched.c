#include "../../include/sched.h"

//2023-04-02 12:45:46 

void switch_to(struct reg* next);


static struct task_struct init_task = INIT_TASK;

struct task_struct *TASK[MAX_TASK] = {&init_task,};
struct task_struct *current = &init_task;

void schedule()
{
	int max_priority = -1;
	bool flag = 0;
	struct task_struct **p = &TASK[MAX_TASK];
	int i = MAX_TASK;
	
	while(--i)
	{
		if(!*--p)continue;
		if((*p)->state == TASK_READY && (*p)->priority > max_priority)
		{
			max_priority = (*p)->priority;
			(*p)->counter = (*p)->priority;
			current = *p;
			flag = 1;
		}
	}
	if(!flag)current = TASK[0];
	struct reg *next = &(current->context);
	switch_to(next);
}

void Init_sched()
{
	printf("Initial sched...\n");
	w_mscratch(0);
	
}
