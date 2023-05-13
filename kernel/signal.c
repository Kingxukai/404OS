#include "../include/signal.h"
#include "../include/type.h"
#include "../include/sched.h"

struct task_struct *current;

void do_signal(int64_t signr)
{
	void (*sa_handler)();
	struct sigaction* sa = current->sigaction + signr - 1;
	
	sa_handler = sa->sa_handler;
	if(sa_handler == SIG_DFL)return;
	if(sa_handler == SIG_IGN)
	{
		if(signr == SIGCHLD)return;
		else do_exit();
	}
	
	if(sa->sa_flags & SA_ONESHOT)
	{
		sa->sa_handler = NULL;
	}
}
