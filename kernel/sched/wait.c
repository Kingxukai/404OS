#include "../../include/unistd.h"

pid_t wait(int *wait_stat)
{
	return waitpid(-1,wait_stat,0);
}
