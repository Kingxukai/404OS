#include "../include/trap.h"
#include "../include/printf.h"
#include "../include/timer.h"
#include "../include/riscv64.h"
#include "../include/sched.h"

extern void trap_vector(void);
extern void do_syscall(struct reg *context);

void Init_trap()
{
	printf("Initial trap...\n");
	w_mtvec((reg64_t)trap_vector);
	//w_mstatus((reg64_t)0x1800);			//here we temporarily set next privilege as 11(machine)
}

void machine_interrupt_handler()	//handle the char from keyboard
{
	uint32_t irq = claim();  
	if(irq == UART0_IRQ)
	{
		uart_console();
	}
	else if(irq)printf("unknown interrupt\n");
	
	if(irq)complete(irq);
}

reg64_t trap_handler(reg64_t cause,reg64_t epc,struct reg *context)
{
	if(cause & 0x8000000000000000)		//interrupt
	{
		switch(cause & 0xfff)
		{
			case 3:
				{
					printf("Machine software interrupt\n");
					break;
				}
			case 7:
				{
					//printf("Machine timer interrupt\n");
					timer_interrupt_handler();
					break;
				}
			case 11:
				{
					//printf("Machine external interrupt\n");
					machine_interrupt_handler();
					break;
				}
			default:printf("unknown interrupt\n");
		}
	}
	else														//exception
	{
		switch(cause & 0xfff)
		{
			case 0:printf("Instruction address misalligned\n");break;
			case 1:printf("Instruction acess fault\n");break;
			case 2:printf("Illegal instruction\n");break;
			case 3:printf("BreakPoint\n");break;
			case 4:printf("Load address  misalligned\n");break;
			case 5:printf("Load acess fault\n");break;
			case 6:printf("Store/AMO address misalligned\n");break;
			case 7:printf("Store/AMO acess fault\n");break;
			case 8:
			{
				printf("Environment call from U-mode\n");
				do_syscall(context);
				goto NO_ERROR;
			}
			case 9:printf("Environment call from S-mode\n");break;
			case 11:printf("Environment call from M-mode\n");break;
			case 12:printf("Instruction page fault\n");break;
			case 13:printf("Load page fault\n");break;
			case 15:printf("Store/AMO page fault\n");break;
			default:printf("unknow fault\n");break;
		}
		printf("mcause:0x%x\nmepc:0x%x\n",cause,epc);
		panic("encounter error\n");			//except cause=8/9/11
		NO_ERROR:
		epc += 4;												//make epc point to next 4 address to avoid infinte loop
	}
	return epc;
}

void cli()
{
	w_mstatus(r_mstatus() & ~EA);
}

void sti()
{
	w_mstatus(r_mstatus() | EA);
}
