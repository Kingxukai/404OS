#ifndef _LOCK_H__
#define _LOCK_H__

#define FLOCK(f) spin_lock(f)
#define UFLOCK(f) spin_unlock(f)

#include "type.h"

typedef struct spin_lock
{
	bool __attribute__((aligned(8))) state;// 1:used 0:unused
}file_lock;

void spin_lock(struct spin_lock* lock);
void spin_unlock(struct spin_lock* lock);

#endif
