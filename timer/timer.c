#include "../include/timer.h"
#include "../include/sched.h"
#include "../include/trap.h"
#include "../include/riscv64.h"

volatile uint64_t jiffies = 0;

void add_timer(uint64_t jiffies, void (*fn)())
{
	if(!fn)return;
	cli();//close interrupt
	
	struct timer_list * p = timer_head;
	while(p->next)
	{
		p = p->next;
	}
	p->next = (struct timer_list *)page_alloc(1);				//temporarily we use 'page_alloc' to alloc, but lately we will use 'malloc' to alloc preciesely
	p = p->next;
	
	p->jiffies = jiffies;
	p->fn = fn;
	
	sti();//enable interrupt
}

void do_timer()
{
	current->time++;
	if(current->pid) 
	{
		if(--(current->counter) > 0)
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
	uint64_t hart = r_mhartid();
	*(uint64_t*)CLIENT_MTIMERCMP(hart) = *(uint64_t*)CLIENT_MTIMER + CLOCK_PIECE;
}

void Init_timer()
{
	printf("Initial timer...\n");
	w_mstatus(r_mstatus() | EA);
	
	w_mie(r_mie() | MTIE);
	
	printf("Initialed All!\n");
}

void timer_interrupt_handler()
{
	timer_selfadd();
	do_timer();
}

