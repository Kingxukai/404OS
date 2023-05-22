#ifndef _LIB_H_
#define _LIB_H_

extern void* _malloc_(uint32_t size);
extern void _free_(void*,int size);
extern pid_t wait();

#define free(adr) _free_((void*)(adr),0)
#define malloc(x) _malloc_(x)

#endif
