#define ASSEMBLE
#include "../include/system.h"

.global gethid
.global getpid

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

.end
