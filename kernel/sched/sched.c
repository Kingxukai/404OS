#include "../../include/sched.h"
#include "../../include/riscv64.h"
#include "../../include/lib.h"

//2023-04-02 12:45:46 

void switch_to(struct reg* next);

static struct task_struct init_task = INIT_TASK;

struct task_struct *TASK[MAX_TASK] = {&init_task,};
struct task_struct *current = &init_task;

static struct Queue_head queue_head[5] = {{NULL},{NULL},{NULL},{NULL},{NULL}};
static struct Queue *tail[5] = {NULL,NULL,NULL,NULL,NULL};			//pointer of each queue's tail

int times = 0;

void set_Queue()																//set the queue
{
	struct task_struct **p = &TASK[MAX_TASK];
	int i = MAX_TASK;
	uint8_t order = 0;
	printf("called : %d\n",times++);
	while(--i)
	{
		if(!*--p || (*p)->in_Queue || (*p)->order < 0)continue;
		if((*p)->state == TASK_READY || (*p)->state == TASK_RUNNING)
		{
			if((*p)->order < 4 && (*p)->state == TASK_RUNNING)
			{
				(*p)->order++;
			}
			order = (*p)->order;
			if(!(queue_head[order].next))
			{
				printf("the size of Queue is: %d\n",sizeof(struct Queue));
				//queue_head[order].next = (struct Queue*)page_alloc(1);
				queue_head[order].next = (struct Queue*)malloc(sizeof(struct Queue));
				tail[order] = queue_head[order].next;
			}
			else
			{
				tail[order]->next = (struct Queue*)malloc(sizeof(struct Queue));
				//tail[order]->next = (struct Queue*)page_alloc(1);
				tail[order] = tail[order]->next;
			}
			
			tail[order]->pid = (*p)->pid;
			tail[order]->next = NULL;
			tail[order]->task = *p;
			
			(*p)->in_Queue = 1;
			(*p)->order = order;
			(*p)->counter = COUNTER(order);
		}
	}
	/*
	for(int j = 0;j<5;j++)
	{
		if(!(queue_head[j].next))continue;
		printf("Queue[%d]:",j+1);
		struct Queue* q = queue_head[j].next;
		while(q)
		{
			printf("task%d\t",q->pid);
			q = q->next;
		}
		printf("\n");
	}*/
}

void schedule()
{
	set_Queue();
	bool flag = 0;
	
	for(int i = 0;i<5;i++)
	{
		if(!(queue_head[i].next))continue;
		flag = 1;
		struct Queue* q = queue_head[i].next;
		current = q->task;
		queue_head[i].next = q->next;
		current->in_Queue = 0;
		current->state = TASK_RUNNING;
		free(q);
		break;
	}
	
	if(!flag)current = TASK[0];
	struct reg *next = &(current->context);
	timer_selfadd();
	switch_to(next);
}

void Init_sched()
{
	printf("Initial sched...\n");
	w_mscratch(0);
	
}
