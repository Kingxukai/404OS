#include "../include/kernel.h"

void kernel_start()
{
	Init();				//exceve task0
	schedule();		//schedule to run task0 in free time
	while(1)
	{
		
	}
}
