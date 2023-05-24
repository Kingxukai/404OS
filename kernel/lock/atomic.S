#a0:save addr
#a1:cmp num

#lock: 
#	return 0-success 1-fail
#unlock:
#	return 0-fail 1-success

.align 4
.global spin_atomic_lock

spin_atomic_lock:
	amoswap.w a0,a1,(a0)
	jr ra	
