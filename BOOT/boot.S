#include<../include/platform.h>

.equ STACK_SIZE 1024
.global _start

.text

_start:
	csrr t0,mhartid
	bnez t0,park
	
	slli t0,t0,10
	la sp,stack + STACK_SIZE
	add sp,t0
	j kernel_start
	
park:
	wfi
	j park	
	
stack:
	.skip STACK_SIZE * CPU_NUM
	.end
