#include "include/kernel.h"

extern void Init_trap();
extern void Init_uart();

void Init()
{
	Init_uart();
	Init_trap();
	/*other init*/
}
