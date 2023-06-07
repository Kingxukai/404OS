#include "../../include/sched.h"
#include "../../include/usr/lib.h"
#include "../../include/signal.h"

extern struct task_struct *current;

static void tell_father(pid_t pid);

pid_t do_exit(int error_code)
{
	if(current->pid)
	{
		int i = MAX_TASK;
		struct task_struct **p = &TASK[MAX_TASK];
		while(--i)
		{
			if(!*--p)continue;
			if((*p)->father_pid == current->pid)			//find every child process,and change their father as 1
			{
				(*p)->father_pid = 1;
				if((*p)->state == TASK_ZOMBINE)					//if his child process is already in TASK_ZOMBINE, tell task1.
				{
					tell_father(1);
				}
			}
		}
		current->state = TASK_ZOMBINE;
		current->counter = 0;
		current->in_Queue = 0;
		current->order = -1;
		
		tell_father(current->father_pid);
		//printk("task%d exit with error_code:%d\n",current->pid,error_code);
		schedule();
	}
	else
	{
		panic("Attempted to kill task 0\n");
	}
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
			return;
		}
	}
	panic("error in releasing a task memory");
}

static void tell_father(pid_t pid)
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
	current->father_pid = 1;
	TASK[1]->signal |= SIG_CHLD;//make his father as process 'INIT'
}
