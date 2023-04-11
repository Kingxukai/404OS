#include "../kernel_about/include/sched.h"

.global trap_vector
.allign 4
.text

trap_vector:
	csrrw t6,mscratch,t6
	
	reg_save t6
	
	mv t5,t6
	
	csrr t6,mscratch
	
	sd t6,240(t5);
	
	csrw mscratch,t5
	
	csrr a0,mcause
	csrr a1,mepc
	call trap_hander
	
	csrw mepc,a0
	
	csrr t6,mscratch
	reg_restore t6
	
	mret

.end
