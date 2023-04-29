#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

extern uint64_t sys_gethid();		//just like syscall format in linux
extern pid_t sys_getpid();
extern pid_t sys_getppid();
extern pid_t sys_fork();

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid,	//0
sys_getpid, //1
sys_getppid,//2
sys_fork,		//3
};

#endif
