#includue<process/incclude/sched.h>

//2023-04-02 12:45:46 

extern void switch_to(struct PCB* next);

void schedule()
{
	struct PCB ** p =&task_struct[MAX_TASK];
	struct PCB *next;
	u8 MAX_priority = LOW;
	int i = MAX_TASK;
	while(i--)
	{
		if(!(*p)--)continue;
		if((*p)->priority > current->priority && (*p)->pirority >= MAX_priority)
		{
			next = *p;
			MAX_priority = (*p)->priority;
		}
	}
	current = next;
	switch_to(next);
}

void init_sched()
{
	struct PCB * next = &task_struct[0];
	asm volatile("csrw mscratch, %0" : : "r" (x));
	
	current = next;
	switch_to(next);
}
