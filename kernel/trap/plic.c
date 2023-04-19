#include "../include/type.h"

uint64_t claim()
{
	uint64_t hart = r_tp();
	uint64_t irq = *(uint64_t *)PLIC_MCLAIM(hart);
	return irq;
}

void complete(uuint64_t64_t irq)
{
	uint64_t hart = r_tp();
	*(uint64_t *)PLIC_MCOMPLETE(hart) = irq;
}
