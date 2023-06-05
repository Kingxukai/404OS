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

.macro context_save base
	sd ra, 0(\base)
	sd sp, 8(\base)
	sd s0, 16(\base)
	sd s1, 24(\base)
	sd s2, 32(\base)
	sd s3, 40(\base)
	sd s4, 48(\base)
	sd s5, 56(\base)
	sd s6, 64(\base)
	sd s7, 72(\base)
	sd s8, 80(\base)
	sd s9, 88(\base)
	sd s10, 96(\base)
	sd s11, 104(\base)
.endm

.macro context_restore base
	ld ra, 0(\base)
	ld sp, 8(\base)
	ld s0, 16(\base)
	ld s1, 24(\base)
	ld s2, 32(\base)
	ld s3, 40(\base)
	ld s4, 48(\base)
	ld s5, 56(\base)
	ld s6, 64(\base)
	ld s7, 72(\base)
	ld s8, 80(\base)
	ld s9, 88(\base)
	ld s10, 96(\base)
	ld s11, 104(\base)
.endm

.globl switch_to
.align 4
switch_to:
#judge that if a0 is 0
	beqz a0,1f
	addi sp,sp,-104
	sd sp,256(a0)
	mv t6,sp
	context_save t6
	
1:	
	csrw sscratch,a1
	csrr t6,sscratch

	ld t5,256(t6)
	beqz t5,2f
	mv sp,t5
	
	mv t6,sp
	context_restore t6
	addi sp,sp,104
	
	ret
	
2:j ret_from_sys_call

.global trap_vector
.align 4
#hardware auto disable interrupt
trap_vector:
	csrrw t6,sscratch,t6

	reg_save t6	
	mv t5,t6
	csrr t6,sscratch
	sd t6,240(t5)
	csrr t6,sepc
	sd t6,248(t5)
	
	csrw sscratch,t5
	
#alarm if stack overflow

	li a0,1
	call set_mode

	mv a0,sp
	call Dect_stack

	csrr a0,scause
	csrr a1,sepc
	csrr a2,sscratch
	
	call trap_handler

ret_from_exception:
	csrr t6,sscratch
	sd a0,248(t6)

ret_from_sys_call:	
	li a0,0
	call set_mode
	csrr t6,sscratch
	ld t5,248(t6)
	csrw sepc,t5
	reg_restore t6

#enable interrupt

	sret

.end
