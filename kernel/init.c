#include "../include/kernel.h"
#include "../include/unistd.h"

extern int task2();

void Init()
{
	/*other init*/
	
	if(fork() == 0)
	{
		execve(task2,NULL,NULL);
	}
	while(1)
	{
		
	}
	panic("unexpected step?!\n");
}
