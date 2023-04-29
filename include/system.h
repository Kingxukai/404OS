#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#ifndef ASSEMBLE
#include "type.h"

extern uint64_t gethid();	//0
extern pid_t getpid();		//1
extern pid_t getppid();		//2
extern pid_t fork(); 			//3

#else

#define NR_GETHID 0
#define NR_GETPID 1
#define NR_GETPPID 2
#define NR_FORK 3

#endif

#endif
