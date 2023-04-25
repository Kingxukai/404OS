#include "../include/type.h"
#include "../include/trap.h"
#include "../include/platform.h"
#include "../include/uart.h"

uint64_t claim()
{
	uint64_t hart = r_tp();
	uint64_t irq = *(uint32_t *)PLIC_MCLAIM(hart);
	return irq;
}

void complete(uint64_t irq)
{
	uint64_t hart = r_tp();
	*(uint32_t *)PLIC_MCOMPLETE(hart) = irq;
}

void Init_plic()
{
	uint64_t hart = r_tp();
	*(uint32_t *)PLIC_PRIORITY(UART0_IRQ) = 1;
	
	*(uint32_t *)PLIC_MENABLE(hart) = (1 << UART0_IRQ);
	
	*(uint32_t *)PLIC_MTHRESHOLD(hart) = 0;

	w_mie(r_mie() | 1 << 11);
	w_mstatus(r_mstatus() | 1 << 3);
}
