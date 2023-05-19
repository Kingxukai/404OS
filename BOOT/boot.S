#include "../include/platform.h"

.equ STACK_SIZE, 1024
.global _start

.text

_start:
	csrr t0, mhartid	
	mv a0, t0									//save the value of hartid in a0, which is an arg of kernel_start
	bnez t0, park							//temporarily we only allow hart0 to run,and other turn to park
	
	slli t0,t0,10							//hartid * 1024
	la sp, stack + STACK_SIZE
	add sp, sp, t0						//alloc stacksize and stack pointer to every hart
	
	la t0,_bss_start					// clear BSS
	la t1,_bss_end
	bgeu	t0, t1, 2f
1:
	sw	zero, (t0)
	addi	t0, t0, 4
	bltu	t0, t1, 1b					//clear BSS end
2:

	li      t0, 0xffffffff
	csrw    pmpaddr0, t0
	li      t0, 0xf
	csrw    pmpcfg0, t0
	
	li t0,MPIE						//MPIE defined in platfrom.h
	csrr t1,mstatus	
	or t0,t0,t1
	csrw mstatus,t0						//set the MPIE
	
	j kernel_start				//the entry of kernel
	
park:
	wfi								//wait for interrupt
	j park	
	
stack:
	.skip STACK_SIZE * CPU_NUM				//alloc each hard stack for STACK_SIZE(1024B)
	.end
