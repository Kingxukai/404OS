#include<stdarg.h>
#include<stddef.h>
#include "../include/lock.h"
#include "../include/print/printk.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1000
#endif
static char buff[BUF_SIZE];

extern struct file_lock* KOUT;

extern int _vprintf(struct file_lock* lock,const char* s, va_list vl,char buf[]);

void printk(const char * s, ... )
{
	int res = 0;
	va_list vl;
	va_start(vl, s);
	res = _vprintf(KOUT,s, vl, buff);
	va_end(vl);
	return res;
}
