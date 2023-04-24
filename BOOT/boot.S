#include "../include/platform.h"

.equ STACK_SIZE, 1024
.global _start

.text

_start:
	csrr t0, mhartid	
	mv tp, t0									//save in tp of hartid
	bnez t0, park
	
	slli t0,t0,10							//hartid * 1024
	la sp, stack + STACK_SIZE
	add sp, sp, t0						//alloc stacksize and stack pointer to every hart
	
	csrw satp,x0							//cancel the virtual memory
	
	
park:
	wfi
	j park	
	
stack:
	.skip STACK_SIZE * CPU_NUM
	.end
