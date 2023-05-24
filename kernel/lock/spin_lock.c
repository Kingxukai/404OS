#include "../../include/lock.h"

static file_lock uart_lock[] = {{0},{0}};	//"file_lock" was defined in include/lock.h,which is spin_lock
const file_lock* STDOUT = &uart_lock[0];
const file_lock* KOUT = &uart_lock[1];

extern spin_atomic_lock(bool* addr,reg64_t cmp_num);

void spin_lock(struct spin_lock* lock)
{
	lock_repeat:
		if(spin_atomic_lock(&lock->state,1))goto lock_repeat;
}

void spin_unlock(struct spin_lock* lock)
{
	if(spin_atomic_lock(&lock->state,0))return;
	else panic("illegal unlock operation!\n");
}
