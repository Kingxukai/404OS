#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#ifndef ASSEMBLE
#include "type.h"

extern reg64_t gethid();		//0
extern reg64_t getpid();		//1

#else

#define NR_GETHID 0
#define NR_GETPID 1

#endif

#endif
