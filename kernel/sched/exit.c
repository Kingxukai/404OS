#include "../../include/sched.h"

extern struct task_struct *current;

void do_exit()
{
	struct task_struct *p = current;
	if(p->pid)
	{
		p->state = TASK_STOP;
		p->counter = 0;
		page_free(p);
	}
	else
	{
		panic("try to kill task 0\n");
	}
}
