#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

#define NR_GETHID 0
#define NR_GETPID 1

extern reg64_t sys_gethid();		//just like syscall format in linux
extern reg64_t sys_getpid();

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid,	//0
sys_getpid, //1
};

#endif
