.global gethid

.align 4
gethid:
	li a7,0
	ecall
	ret

.end
