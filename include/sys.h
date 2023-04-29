#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

#define NR_GETHID 0
#define NR_GETPID 1
#define NR_GETPPID 2

extern reg64_t sys_gethid();		//just like syscall format in linux
extern reg64_t sys_getpid();
extern reg64_t sys_getppid();

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid,	//0
sys_getpid, //1
sys_getppid,//2
};

#endif
