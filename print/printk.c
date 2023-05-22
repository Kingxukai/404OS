#include<stdarg.h>
#include<stddef.h>
#include "../include/lock.h"
#include "../include/print/printk.h"

static char buf[1000];

extern struct file_lock* KOUT;

extern int _vprintf(struct file_lock* lock,const char* s, va_list vl);

void printk(const char * s, ... )
{
	int res = 0;
	va_list vl;
	va_start(vl, s);
	res = _vprintf(KOUT,s, vl);
	va_end(vl);
	return res;
}
