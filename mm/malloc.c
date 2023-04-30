#include "../include/kernel.h"

struct page_table_entry
{
	uint64_t index;
	uint64_t sit;
};
