#include "../include/timer.h"
#include "../include/sched.h"
#include "../include/trap.h"
#include "../include/asm/riscv64.h"
#include "../include/usr/lib.h"
#include "../include/sbi.h"

extern void cli();				//defined in trap/trap.c
extern void sti();

volatile uint64_t jiffies = 0;

static struct timer_list time_head = {0,NULL,0,NULL};
static struct timer_list *timer_head = &time_head;

void add_timer(uint64_t _jiffies, void (*fn)())
{
	if(!fn)return;
	//cli();//close interrupt
	
	struct timer_list * p = timer_head;
	while(p->next)
	{
		p = p->next;
	}
	p->next = (struct timer_list *)page_alloc(1);
	p = p->next;
	
	p->jiffies = jiffies;
	p->_jiffies = _jiffies;
	p->fn = fn;
	
	//sti();//enable interrupt
}


void do_timer()
{
	struct timer_list *p = timer_head;
	while(p->next)
	{
		p = p->next;
		if(!p->fn)continue;
		if(p->jiffies + p->_jiffies <= jiffies)(*(p->fn))();
	}
									//sched
	current->time++;
	if(current->pid) 
	{
		if(--(current->counter) > 0 && (current->state == TASK_RUNNING || current->state == TASK_READY))
		{
			timer_selfadd();
			return;
		}
	}
	schedule();
}

void timer_selfadd()
{
	jiffies++;
	SET_TIMER();
}

void Init_timer()
{
	printk("Initial timer...\n");
	w_sstatus(r_sstatus() | EA);
	
	w_sie(r_sie() | STIE);
	
	//timer_selfadd();
}

void timer_interrupt_handler()
{
	timer_selfadd();
	do_timer();
}

