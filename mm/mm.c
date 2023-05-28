#include "../include/type.h"

void *memset(void *dest, int c, uint64_t n)
{
    char *p = dest;
    for (int i = 0; i < n; ++i)
    {
    	*(p++) = c;
    }
    return dest;
}
