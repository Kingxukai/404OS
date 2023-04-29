#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#ifndef ASSEMBLE
#include "type.h"

extern reg64_t gethid();		//0
extern reg64_t getpid();		//1
extern reg64_t getppid();		//2

#else

#define NR_GETHID 0
#define NR_GETPID 1
#define NR_GETPPID 2

#endif

#endif
