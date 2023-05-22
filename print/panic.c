#include "../include/print/printk.h"

void panic(char *s)
{
	printf("panic: ");
	printf(s);
	printf("\n");
	while(1){};
}
