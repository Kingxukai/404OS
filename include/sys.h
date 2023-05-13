#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

extern uint64_t sys_gethid();		//just like syscall format in linux
extern pid_t sys_getpid();
extern pid_t sys_getppid();
extern pid_t sys_fork();
extern pid_t sys_fork();
extern int sys_execve();
extern pid_t sys_exit();
extern pid_t sys_waitpid(pid_t pid,uint64_t* stat_addr,int options);

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid,	//0
sys_getpid, 	//1
sys_getppid,	//2
sys_fork,	//3
sys_execve,	//4
sys_exit,	//5
sys_waitpid,	//6
};

#endif
