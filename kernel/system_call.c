#include "../include/system.h"
#include "../include/sched.h"

inline _syscall0(uint64_t,gethid)	//0
inline _syscall0(pid_t,getpid)	//1
inline _syscall0(pid_t,getppid)//2
inline _syscall0(pid_t,fork)	//3
inline _syscall3(int, execve, const char *, filepath,char * const *, argv, char * const *, envp)	//4
inline _syscall0(pid_t, exit)	//5
inline _syscall0(void *,malloc)	//6
