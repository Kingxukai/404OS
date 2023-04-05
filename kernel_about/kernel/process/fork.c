u16 get_newpid()
{
	u16 i = 0;
	struct PCB** p = &task_struct[0];
	while(++i<MAX_TASK)
	{
		if(*++p)continue;
		return i;
	}
	return MAX_TASK;
}

u8 fork()
{
	u16 new_id = 0;
	if( (new_id = get_newpid()) == MAX_TASK )printf("No free task id to create!\n");
	else
	{
		struct PCB *p = (struct * PCB)get_free_page();
		if(!p) return 																//something wrong in page alloc
		task_struct[new_id] = p;
		
		*p = *current;
		p->pid = new_id;
		p->father_id = current->pid;
		p->state = TASK_READY;
		p->start_time = jiffies;
		p->time = 0;
		p->priority = current->priority;
		p->priority = p->counter;
		p->context = {0};															//not eventually value
	}
	return 0;
}

void task0()
{
	printf("task0 is created\n");
	printf("task0 is running\n");
	schedule();
}
