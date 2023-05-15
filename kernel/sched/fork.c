#include "../../include/sched.h"
#include "../../include/kernel.h"
#include "../../include/timer.h"
#include "../../include/trap.h"
#include "../../include/lib.h"

void switch_to(struct reg* last, struct reg* next);
reg64_t ret_from_sys_call();

uint8_t task_stack[MAX_TASK][STACK_SIZE];			//each task occupy 1024B stack size

extern struct task_struct *current;

pid_t NEW_PID = 0;					//newest PID
int NEW_PCBID = 0;					//newest PCB id

int find_new_id()
{
	pid_t i = 0;
	struct task_struct ** p = &TASK[0];
	NEW_PID++;
	while(++i<MAX_TASK)
	{
		if(*++p)continue;
		NEW_PCBID = i;
		return NEW_PCBID;
	}
	return MAX_TASK;
}

void memcpy(reg8_t* from, reg8_t* to, uint64_t size)
{
	while(size--)
	{
		*to = *from;
		to++;
		from++;
	}
}

static void copy_memory(reg64_t sp)
{
	reg8_t *old_addr_start = (reg64_t)&task_stack[current->pcb_id][STACK_SIZE - 1];
	reg8_t *old_addr_end = (reg64_t)&task_stack[current->pcb_id][0];
	reg8_t *new_addr_start = (reg8_t *)sp;
	while(old_addr_start >= old_addr_end)//copy task stack
	{
		*new_addr_start = *old_addr_start;
		new_addr_start--;
		old_addr_start--;
	}
}

pid_t copy_process()
{
	cli();
	struct task_struct *p = (struct task_struct *)malloc(sizeof(struct task_struct));
	if(!p) panic("something wrong in page alloc,please check\n");																//something wrong in page alloc
	TASK[NEW_PCBID] = p;
	
	p->pid = NEW_PID;
	p->father_pid = current->pid;
	p->pcb_id = NEW_PCBID;
	p->state = TASK_READY;
	p->start_time = jiffies;
	p->time = 0;
	p->priority = current->priority;
	p->counter = p->priority;
	p->order = 0;
	p->in_Queue = 0;
	p->signal = 0;
	
	for(int i = 0;i < 32;i++)//copy the sigaction
	{
		p->sigaction[i].sa_handler = current->sigaction[i].sa_handler;
		p->sigaction[i].sa_mask = current->sigaction[i].sa_mask;
		p->sigaction[i].sa_flags = current->sigaction[i].sa_flags;
	}
	p->exit_code = 0;

	p->context.ra = (reg64_t)ret_from_sys_call;
	p->context.sp = (reg64_t)&task_stack[p->pcb_id][STACK_SIZE-1];	//if just alloc the new process a new stack,what will happen? yes,the local variable will disapear because it pointing to a new space with none data while new task executing. SO,we need to copy mm.
	copy_memory(p->context.sp);
	p->context.sp = p->context.sp - ((reg64_t)(&task_stack[current->pcb_id][STACK_SIZE-1]) - (current->context.sp));//get the relative address
	p->context.gp = (reg64_t)p;//save the address of task_struct in gp
	p->context.tp = current->context.tp;
	p->context.t0 = current->context.t0;
	p->context.t1 = current->context.t1;
	p->context.t2 = current->context.t2;
	p->context.s0 = (reg64_t)&task_stack[p->pcb_id][STACK_SIZE-1] - (current->context.sp - current->context.s0);
	p->context.s1 = current->context.s1;
	p->context.a0 = 0;										//so the return value of fork in new process is 0
	p->context.a1 = current->context.a1;
	p->context.a2 = current->context.a2;
	p->context.a3 = current->context.a3;
	p->context.a4 = current->context.a4;
	p->context.a5 = current->context.a5;
	p->context.a6 = current->context.a6;
	p->context.a7 = current->context.a7;
	p->context.s2 = current->context.s2;
	p->context.s3 = current->context.s3;
	p->context.s4 = current->context.s4;
	p->context.s5 = current->context.s5;
	p->context.s6 = current->context.s6;
	p->context.s7 = current->context.s7;
	p->context.s8 = current->context.s8;
	p->context.s9 = current->context.s9;
	p->context.s10 = current->context.s10;
	p->context.s11 = current->context.s11;
	p->context.t3 = current->context.t3;
	p->context.t4 = current->context.t4;
	p->context.t5 = current->context.t5;
	p->context.t6 = current->context.t6;
	p->context.epc = current->context.epc + 4;	//don't ecall again to avoid endless loop
	
	sti();
	return p->pid;
}
