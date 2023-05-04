#include "../../include/sched.h"

extern struct task_struct *current;

pid_t do_exit()
{
	struct task_struct *p = current;
	if(p->pid)
	{
		p->state = TASK_ZOMBINE;
		p->counter = 0;
		p->in_Queue = 0;
		p->order = -1;
		page_free(p);
		printf("task%d exit\n",p->pid);
		schedule();
	}
	else
	{
		panic("Attempted to kill task 0\n");
	}
	return 0;
}
