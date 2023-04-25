#include "../include/trap.h"
#include "../include/printf.h"
#include "../include/timer.h"

extern void trap_vector(void);

void Init_trap()
{
	w_mtvec((reg64_t)trap_vector);
	w_mstatus((reg64_t)0x1800);			//here we temporarily set next privilege as 11(machine)
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

reg64_t trap_handler(reg64_t cause,reg64_t epc)
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
			case 8:printf("Environment call from U-mode\n");break;
			case 9:printf("Environment call from S-mode\n");break;
			case 11:printf("Environment call from M-mode\n");break;
			case 12:printf("Instruction page fault\n");break;
			case 13:printf("Load page fault\n");break;
			case 15:printf("Store/AMO page fault\n");break;
			default:printf("unknow fault\n");break;
		}
		printf("mcause:%x\nmepc:%x\n",cause,epc);
		epc += 4;												//make epc point to next 4 address to avoid infinte loop
		panic("encounter wrong\n");
	}
	return epc;
}
