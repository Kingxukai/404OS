#ifndef _SCHED_H__
#define _SCHED_H__

#include "../../include/platform.h"
#include "process.h"

void switch_to(struct PCB* next);
void reg_save(reg64 base);
void reg_restore(reg64 base);
void schedule();
void init_sched();
void w_mscratch(reg64 reg);

#endif
