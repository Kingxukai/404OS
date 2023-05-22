#include "../../include/lock.h"

static struct file_lock uart_lock[] = {{0},{0}};
const struct file_lock* STDOUT = &uart_lock[0];
const struct file_lock* KOUT = &uart_lock[1];

void _lockfile(struct file_lock* lock)
{
	lock_repeat:
		if(lock->state)goto lock_repeat;
		else lock->state = 1;
}

void _unlockfile(struct file_lock* lock)
{
	if(lock->state)lock->state = 0;
	else panic("illegal unlock operation!\n");
}
