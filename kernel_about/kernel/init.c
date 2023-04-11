#include "include/kernel.h"

extern Init_trap();
extern Init_uart();

void Init()
{
	Init_uart();
	Init_trap();
	/*other init*/
}

void Init_uart()
{
	
}
