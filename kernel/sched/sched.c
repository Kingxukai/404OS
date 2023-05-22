#include "../../include/sched.h"
#include "../../include/asm/riscv64.h"
#include "../../include/usr/lib.h"

#define BLOCK_SIG (SIG_KILL | SIG_STOP)				//except SIG_KILL and SIG_STOP

//2023-04-02 12:45:46 

void switch_to(struct reg* last, struct reg* next);

static struct task_struct init_task = INIT_TASK;

struct task_struct *TASK[MAX_TASK] = {&init_task,};
struct task_struct *current = &init_task;

static struct Queue_head queue_head[5] = {{NULL},{NULL},{NULL},{NULL},{NULL}};
static struct Queue *tail[5] = {NULL,NULL,NULL,NULL,NULL};			//pointer of each queue's tail

static void show_task_queue();

int times = 0;

static void set_Queue()																//set the queue
{
	struct task_struct **p = &TASK[MAX_TASK];
	int i = MAX_TASK;
	uint8_t order = 0;
 	
	while(--i)
	{
		if(!*--p ||(*p)->order < 0)continue;
		if(!(*p)->in_Queue)
		{
			if((*p)->state == TASK_READY || (*p)->state == TASK_RUNNING)
			{
				if((*p)->order < 4 && (*p)->state == TASK_RUNNING)
				{
					(*p)->order++;
				}
				order = (*p)->order;
				if(!(queue_head[order].next))
				{
					queue_head[order].next = (struct Queue*)malloc(sizeof(struct Queue));
					tail[order] = queue_head[order].next;
				}
				else
				{
					tail[order]->next = (struct Queue*)malloc(sizeof(struct Queue));
					tail[order] = tail[order]->next;
				}
				
				tail[order]->pid = (*p)->pid;
				tail[order]->next = NULL;
				tail[order]->task = *p;
				
				(*p)->state = TASK_READY;
				(*p)->in_Queue = 1;
				(*p)->order = order;
				(*p)->counter = COUNTER(order);
			}
		}
		else//remove the task which is not in TASK_RUNNING or TASK_READY from the ready queue
		{
			if((*p)->state == TASK_RUNNING || (*p)->state == TASK_READY)continue;
			order = (*p)->order;
			struct Queue *q = queue_head[order].next;
			struct Queue *last = NULL;
			do
			{
				if(q->pid == (*p)->pid)break;
				if(q->next)
				{
					last = q;
					q = q->next;
				}
				else panic("error in remove task from ready queue!?\n");
			}while(1);
			
			if(!last)//if the task is located in first space of queue
				queue_head[order].next = q->next;
			else 
				last->next = q->next;
			if(q == tail[i])tail[i] = last;
			printk("remove task%d\n",q->pid);
			free(q);
		}
	}

	//show_task_queue();

}

static void alter_state()
{
	struct task_struct **p = &TASK[MAX_TASK];
	int i = MAX_TASK;
	while(--i)
	{
		if(!*--p)continue;
		if((*p)->state == TASK_WAIT)
		{
			(*p)->state  = TASK_READY;
		}
	}
}

void schedule()
{
	alter_state();
	set_Queue();
	bool flag = 0;
	struct task_struct* next;
	
	for(int i = 0;i<5;i++)
	{
		if(!(queue_head[i].next))continue;
		flag = 1;
		struct Queue* q = queue_head[i].next;
		next = q->task;
		queue_head[i].next = q->next;
		next->in_Queue = 0;
		next->state = TASK_RUNNING;
		free(q);
		break;
	}
	
	if(!flag)next = TASK[0];
	if(current == next)return;
	struct task_struct* last = current;
	current = next;
	switch_to(&(last->context), &(next->context));
}

void Init_sched()
{
	printk("Initial sched...\n");
	w_mscratch((reg64_t)&(TASK[0]->context));
	
	for(int i=1;i<MAX_TASK;i++)		//clear the TASK
	{
		TASK[i] = NULL;
	}
	
}

void Dect_stack(reg64_t sp)
{
	reg64_t T = (reg64_t)&task_stack[current->pcb_id][STACK_SIZE-1];
	reg64_t L = (reg64_t)&task_stack[current->pcb_id][0];
	if(sp > T || sp < L )
	{
		printk("$SP:0X%x STACK:0X%x~0X%x\n",sp,L,T);
		panic("STACK OVERFLOW!\n");
	}
}

void show_task(pid_t pid)
{
	int i = MAX_TASK;
	while(--i)
	{
		if(!TASK[i])continue;
		if(TASK[i]->pid == pid)break;
	}
	if(TASK[i])
	{
		printk("PID:%d\n",TASK[i]->pid);
		printk("Father PID:%d\n",TASK[i]->father_pid);
		printk("pcb_id:%d\n",TASK[i]->pcb_id);
		printk("state:%d\n",TASK[i]->state);
		printk("start time:%d\n",TASK[i]->start_time);
		printk("time:%d\n",TASK[i]->time);
		printk("priority:%d\n",TASK[i]->priority);
	}
	else
	{
		printk("pid don't exist yet\n");
	}
}

static void show_task_queue()			//in order to test the queue of task
{
	struct Queue *q;
	for(int i = 0;i<5;i++)
	{
		if(!queue_head[i].next)continue;
		q = queue_head[i].next;
		printk("Queue[%d]:",i);
		while(1)
		{
			printk("task%d ",q->pid);
			if(q->next)
					q = q->next;
			else 
				break;
		}
		printk("\ntail[%d]:%x\t",i,tail[i]);
		printk("\ttail[%d]:%d,next:%x",i,tail[i]->pid,tail[i]->next);
		printk("\n");
	}
	printk("----------\n");
}
