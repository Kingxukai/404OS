#ifndef _SYS_H__
#define _SYS_H__

#include "type.h"
#include "asm/system.h"

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
[NR_gethid] = sys_gethid,	
[NR_getpid] = sys_getpid, 
[NR_getppid] = sys_getppid,
[NR_fork] = sys_fork,	
[NR_execve] = sys_execve,	
[NR_exit] = sys_exit,	
[NR_waitpid] = sys_waitpid,	
[NR_shutdown] = sys_shutdown,	
};

#endif
