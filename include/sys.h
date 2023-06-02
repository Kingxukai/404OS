#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"

extern uint64_t sys_gethid();		//just like syscall format in linux
extern pid_t sys_getpid();
extern pid_t sys_getppid();
extern pid_t sys_fork();
extern pid_t sys_fork();
extern int sys_execve(const char *filepath,char * const * argv,char * const * envp);
extern pid_t sys_exit(int error_code);
extern pid_t sys_waitpid(pid_t pid,uint64_t* stat_addr,int options);
extern int sys_shutdown();

sys_func sys_call_table[] = {//sys_func defined in include/type.h
sys_gethid,	//0
sys_getpid, 	//1
sys_getppid,	//2
sys_fork,	//3
sys_execve,	//4
sys_exit,	//5
sys_waitpid,	//6
sys_shutdown,	//7
};

#endif
