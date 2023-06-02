#ifndef _MACRO_H__
#define _MACRO_H__

#define MAX(a,b) (a>b?a:b)

#define MIN(a,b) (a>b?b:a)

#define CEIL_DIVIDE(x, y) (((x) + (y)-1) / (y))

#define ASSERT(cond)                                                             \
    do {                                                                         \
        if (!(cond)) {                                                           \
            printf("\33[1;31m[%s,%d,%s] ASSERT: \"" #cond "\" failed \t \33[0m", \
                   __FILE__, __LINE__, __func__);                                \
            panic("assert failed");                                              \
        }                                                                        \
    } while (0)

#endif
