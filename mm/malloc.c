#include "../include/kernel.h"
#include "../mm/page.c"

struct page_table_entry {
    unsigned long index;
    unsigned long pet;
}
