#ifndef _KERNEL_H__
#define _KERNEL_H__

#include<stddef.h>
#include "platform.h"
#include "type.h"
#include "sched.h"
#include "trap.h"
#include "print/printk.h"
#include "mm.h"

#define MACHINE_MODE (3 << 11)
#define USER_MODE (~(3<<11))

#endif
