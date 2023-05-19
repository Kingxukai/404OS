.macro reg_save base
	sd ra, 0(\base)
	sd sp, 8(\base)
	sd gp, 16(\base)
	sd tp, 24(\base)
	sd t0, 32(\base)
	sd t1, 40(\base)
	sd t2, 48(\base)
	sd s0, 56(\base)
	sd s1, 64(\base)
	sd a0, 72(\base)
	sd a1, 80(\base)
	sd a2, 88(\base)
	sd a3, 96(\base)
	sd a4, 104(\base)
	sd a5, 112(\base)
	sd a6, 120(\base)
	sd a7, 128(\base)
	sd s2, 136(\base)
	sd s3, 144(\base)
	sd s4, 152(\base)
	sd s5, 160(\base)
	sd s6, 168(\base)
	sd s7, 176(\base)
	sd s8, 184(\base)
	sd s9, 192(\base)
	sd s10, 200(\base)
	sd s11, 208(\base)
	sd t3, 216(\base)
	sd t4, 224(\base)
	sd t5, 232(\base)
	.endm

.macro reg_restore base
	ld ra, 0(\base)
	ld sp, 8(\base)
	ld gp, 16(\base)
	ld tp, 24(\base)
	ld t0, 32(\base)
	ld t1, 40(\base)
	ld t2, 48(\base)
	ld s0, 56(\base)
	ld s1, 64(\base)
	ld a0, 72(\base)
	ld a1, 80(\base)
	ld a2, 88(\base)
	ld a3, 96(\base)
	ld a4, 104(\base)
	ld a5, 112(\base)
	ld a6, 120(\base)
	ld a7, 128(\base)
	ld s2, 136(\base)
	ld s3, 144(\base)
	ld s4, 152(\base)
	ld s5, 160(\base)
	ld s6, 168(\base)
	ld s7, 176(\base)
	ld s8, 184(\base)
	ld s9, 192(\base)
	ld s10, 200(\base)
	ld s11, 208(\base)
	ld t3, 216(\base)
	ld t4, 224(\base)
	ld t5, 232(\base)
	ld t6, 240(\base)
.endm

.globl switch_to
.align 4
switch_to:
#judge that if a0 is 0
	beqz a0,1f
	reg_save a0
	
1:
	csrw mscratch,a1

	mv t6,a1
	ld t5,248(t6)
	csrw mepc,t5
	reg_restore t6
	
#it's a necessary step which is avoid restoring the context again as we return from switch_to to ret_from_sys_call
#rather than ret_from_exception

#save the value of t5
	csrrw t6,mscratch,t6
	addi sp,sp,-8
	
#use t5 to save addr of ret_from_sys_call and then put it to context.ra
	sd t5,(sp)
	la t5,ret_from_sys_call
	
	sd t5,(t6)

#resotre the value of t5
	ld t5,(sp)
	addi sp,sp,8
	
	csrrw t6,mscratch,t6

	ret

.global trap_vector
.global ret_from_sys_call
.align 4
#hardware auto disable interrupt
trap_vector:
	csrrw t6,mscratch,t6
	
#this step is aim to save ra in context.temp and the addr of ret_from_exception and reload it to ra after timer_interrupt_handler() in trap_handler()

	sd ra,256(t6)
	la ra,ret_from_exception
	reg_save t6	
	mv t5,t6
	csrr t6,mscratch
	sd t6,240(t5)
	csrr t6,mepc
	sd t6,248(t5)
	
	csrw mscratch,t5
	
#alarm if stack overflow

	mv a0,sp
	call Dect_stack

	csrr a0,mcause
	csrr a1,mepc
	csrr a2,mscratch
	
	call trap_handler

ret_from_exception:
	csrw mepc,a0
	
	csrr t6,mscratch
	reg_restore t6

#without reg_resotre	

ret_from_sys_call:
	csrr t6,mscratch
	ld ra,256(t6)
	sd ra,(t6)
#enable interrupt

	mret

.end
