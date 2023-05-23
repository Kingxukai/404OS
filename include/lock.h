#ifndef _LOCK_H__
#define _LOCK_H__

#define FLOCK(f) _lockfile(f)
#define UFLOCK(f) _unlockfile(f)

#include "type.h"

struct file_lock
{
	bool state;// 1:used 0:unused
};

void _lockfile(struct file_lock* lock);
void _unlockfile(struct file_lock* lock);

#endif
