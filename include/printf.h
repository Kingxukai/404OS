#ifndef _PRINTF_H__
#define _PRINTF_H__

#include "uart.h"

int printf(const char* s, ...);
void panic(char *s);

#endif
