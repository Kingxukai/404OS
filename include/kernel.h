#ifndef _KERNEL_H__
#define _KERNEL_H__

#include "platform.h"
#include "type.h"
#include "sched.h"
#include "trap.h"
#include "printf.h"
#include "stddef.h"

void *page_alloc(int npages);
void page_free(void *p);

#endif
