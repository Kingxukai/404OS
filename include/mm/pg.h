#ifndef _PG_H__
#define _PG_H__

#include "../type.h"

typedef uint64_t* PageTable_t;//页表
typedef uint64_t PTE_t;//页表项

#define PAGE_OFF 12

#define PTE_D (1<<7)
#define PTE_A (1<<6)
#define PTE_G (1<<5)
#define PTE_U (1<<4)
#define PTE_X (1<<3)
#define PTE_W (1<<2)
#define PTE_R (1<<1)
#define PTE_V (1<<0)

#define PAGE_ALIGN(addr) (addr & 0xfffffffffffff000)

#endif
