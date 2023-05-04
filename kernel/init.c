#include "../include/kernel.h"
#include "../include/unistd.h"

extern void task1();

void Init()
{
	/*other init*/
	
	if(fork() == 0)
	{
		execve(task1,NULL,NULL);
	}
	while(1)
	{
		
	}
	panic("unexpected step?!\n");
}
