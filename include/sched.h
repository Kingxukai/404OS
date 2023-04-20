#ifndef _SCHED_H__
#define _SCHED_H__

#include "platform.h"
#include "process.h"
#include "type.h"

void switch_to(struct task_struct* next);
void reg_save(reg64_t base);
void reg_restore(reg64_t base);
void schedule();
void Init_sched();

#endif
