#include "../include/type.h"
#include "../include/trap.h"

uint64_t claim()
{
	uint64_t hart = r_mhartid();
	uint64_t irq = *(uint64_t *)PLIC_MCLAIM(hart);
	return irq;
}

void complete(uint64_t irq)
{
	uint64_t hart = r_mhartid();
	*(uint64_t *)PLIC_MCOMPLETE(hart) = irq;
}
