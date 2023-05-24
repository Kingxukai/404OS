#include "../include/trap.h"
#include "../include/print/uart.h"
#include "../include/print/printk.h"
#include "../include/timer.h"
#include "../include/asm/riscv64.h"
#include "../include/sched.h"

extern void trap_vector(void);
extern void do_syscall(struct reg *context);
extern void ret_from_sys_call();

void Init_trap()
{
	printk("Initial trap...\n");
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
	else if(irq)printk("unknown interrupt\n");
	
	if(irq)complete(irq);
}

static void show_register();

reg64_t trap_handler(reg64_t cause,reg64_t epc,struct reg *context)
{
	reg64_t ra;
	asm volatile("mv %0,ra":"=r"(ra));
	if(cause & 0x8000000000000000)		//interrupt
	{
		switch(cause & 0xfff)
		{
			case 3:
				{
					printk("Machine software interrupt\n");
					break;
				}
			case 7:
				{
					//printk("\nMachine timer interrupt\n");
					timer_interrupt_handler();
					ra = context->ra;
					break;
				}
			case 11:
				{
					//printk("Machine external interrupt\n");
					machine_interrupt_handler();
					break;
				}
			default:printk("unknown interrupt\n");
		}
	}
	else														//exception
	{
		switch(cause & 0xfff)
		{
			case 0:printk("Instruction address misalligned\n");break;
			case 1:printk("Instruction acess fault\n");break;
			case 2:printk("Illegal instruction\n");break;
			case 3:printk("BreakPoint\n");break;
			case 4:printk("Load address misalligned\n");break;
			case 5:printk("Load acess fault\n");break;
			case 6:printk("Store/AMO address misalligned\n");break;
			case 7:printk("Store/AMO acess fault\n");break;
			case 8:
			{
				//printk("Environment call from U-mode\n");
				do_syscall(context);
				goto NO_ERROR;
			}
			case 9:printk("Environment call from S-mode\n");goto NO_ERROR;;
			case 11:
			{
				printk("Environment call from M-mode\n");
				panic("OOPS!!! it's forbiddened temporily ecall from M-mode\n");
				goto NO_ERROR;
			}
			case 12:printk("Instruction page fault\n");break;
			case 13:printk("Load page fault\n");break;
			case 15:printk("Store/AMO page fault\n");break;
			default:printk("unknow fault\n");break;
		}
		printk("\nmcause:0x%x\nmepc:0x%x\n",cause,epc);
		panic("encounter error\n");			//except cause=8/9/11
		NO_ERROR:
		epc += 4;												//make epc point to next 4 address to avoid infinte loop
	}
	asm volatile("addi sp,sp,64");
	asm volatile("mv a0,%0"::"r"(epc));
	asm volatile("mv ra,%0"::"r"(ra));
	asm volatile("ret");
}
/*
void cli()													//close interrupt
{
	w_mstatus(r_mstatus() & ~EA);
}

void sti()													//enable interrupt
{
	w_mstatus(r_mstatus() | EA);
}*/

/*
static void show_register()
{
	reg64_t reg;
	asm volatile("mv %0,a5":"=r"(reg));
	printk("a5:%x\n",reg);
}*/
