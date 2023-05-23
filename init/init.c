#include "../include/kernel.h"
#include "../include/usr/unistd.h"

extern int task2();

void Init()
{
	/*other init*/
	
	if(fork() == 0)
	{
		char *argv[]={task2};
		execve(NULL,argv,NULL);
	}
	while(1)
	{
		
	}
	panic("unexpected step?!\n");
}
