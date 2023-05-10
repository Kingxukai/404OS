#include "../../include/sched.h"
#include "../../include/lib.h"
#include "../../include/signal.h"

extern struct task_struct *current;

void tell_father(pid_t pid);

pid_t do_exit()
{
	if(current->pid)
	{
		int i = MAX_TASK;
		struct task_struct **p = &TASK[MAX_TASK];
		while(--i)
		{
			if(!*--p)continue;
			if((*p)->father_pid == current->pid)			//find every child process,and change their father as 0
			{
				(*p)->father_pid = 0;
				if((*p)->state == TASK_ZOMBINE)					//if his child process is already in TASK_ZOMBINE, tell task0.
				{
					tell_father(0);
				}
			}
		}
		struct task_struct *q = current;
		q->state = TASK_ZOMBINE;
		q->counter = 0;
		q->in_Queue = 0;
		q->order = -1;
		
		tell_father(0);
		printf("task%d exit\n",q->pid);
		schedule();
	}
	else
	{
		panic("Attempted to kill task 0\n");
	}
	return 0;
}

void release(struct task_struct* p)			//release certain memory of a PCB
{
	if(!p)return;
	for (int i = 1;i < MAX_TASK;i++)
	{
		if(!TASK[i])continue;
		if(TASK[i] == p)
		{
			TASK[i] = NULL;
			free(p);
			schedule();
			return;
		}
	}
	panic("error in releasing a task memory");
}

void tell_father(pid_t pid)
{
	if(pid)				
	{
		for(int i = 1;i < MAX_TASK;i++)
		{
			if(!TASK[i])continue;
			if(TASK[i]->pid != pid)continue;
			TASK[i]->signal |= SIG_CHLD;
			return;
		}
	}
	//father process dont exist or has been exited
	current->father_pid = 0;
	TASK[0]->signal |= SIG_CHLD;//make his father as process 'INIT'
}
