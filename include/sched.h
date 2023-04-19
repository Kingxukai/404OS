#ifndef _SCHED_H__
#define _SCHED_H__

#include "platform.h"
#include "process.h"
#include "kernel.h"

void switch_to(struct task_struct* next);
void reg_save(reg64 base);
void reg_restore(reg64 base);
void schedule();
void Init_sched();

#endif
