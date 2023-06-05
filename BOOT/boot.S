#include "../include/platform.h"

.equ STACK_SIZE, 1024
.global _start

.text

_start:
	mv tp,a0				//the value of hartid is in a0, which is an arg of kernel_start
	bnez tp, park							//temporarily we only allow hart0 to run,and other turn to park
	mv t0,tp
	
	slli t0,t0,10							//hartid * 1024
	la sp, stack + STACK_SIZE
	add sp, sp, t0						//alloc stacksize and stack pointer to every hart
	
	#la t0,_bss_start					// clear BSS
	#la t1,_bss_end
	#bgeu	t0, t1, 2f
#1:
	#sw	zero, (t0)
	#addi	t0, t0, 4
	#bltu	t0, t1, 1b					//clear BSS end
#2:

	#li      t0, 0xffffffff
	#csrw    pmpaddr0, t0
	#li      t0, 0xf
	#csrw    pmpcfg0, t0
	
	li t0,SPIE						//SPIE defined in platfrom.h
	csrr t1,sstatus	
	or t0,t0,t1
	csrw sstatus,t0						//set the SPIE
	
	j kernel_start				//the entry of kernel
	
park:
	wfi								//wait for interrupt
	j park	
	
stack:
	.skip STACK_SIZE * CPU_NUM				//alloc each hard stack for STACK_SIZE(1024B)
	.end
