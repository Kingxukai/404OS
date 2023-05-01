#define ASSEMBLE
#include "../include/system.h"

.global gethid
.global getpid
.global getppid
.global fork

.text
.align 4

gethid:
	li a7,NR_GETHID
	ecall
	ret

getpid:
	li a7,NR_GETPID
	ecall
	ret

getppid:
	li a7,NR_GETPPID
	ecall
	ret
	
fork:
	li a7,NR_FORK
	ecall
	j r
	li a0,0
	r:
	ret
.end
