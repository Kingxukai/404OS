#include "../include/asm/system.h"
#include "../include/sched.h"
#include "../include/usr/unistd.h"
#include "../include/signal.h"

inline _syscall0(uint64_t,gethid)	//0
inline _syscall0(pid_t,getpid)	//1
inline _syscall0(pid_t,getppid)//2
inline _syscall0(pid_t,fork)	//3
inline _syscall3(int, execve, const char *, filepath,char * const *, argv, char * const *, envp)	//4
inline _syscall1(pid_t, exit, int, error_code)	//5
inline _syscall3(pid_t, waitpid, pid_t, pid, uint64_t*, stat_addr, int, options)	//6

void ret_from_syscall()
{
	int i = 0;
	if(current->signal)
	{
		uint32_t sig_bit = 1;
		while(++i<23)
		{
			if(current->signal & sig_bit)//the lowest bit which is 1
			{
				current->signal &= ~(sig_bit);
				break;
			}
			sig_bit <<= 1;
		}
	}
	do_signal(i);
}
