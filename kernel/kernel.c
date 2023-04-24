#include "../include/kernel.h"

void kernel_start()
{
	printf("Hello 404OS\n");
	Init();				//exceve task0
	schedule();		//schedule to run task0 in free time
	while(1)
	{
		
	}
}
