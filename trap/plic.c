//ref  <https://www.bilibili.com/video/BV1Q5411w7z5>
#include "../include/type.h"
#include "../include/trap.h"
#include "../include/platform.h"
#include "../include/print/uart.h"
#include "../include/print/printk.h"
#include "../include/asm/riscv64.h"
#include "../include/disk/virtio.h"

uint64_t claim()
{
	uint64_t hart = r_mhartid();
	uint64_t irq = *(uint32_t *)PLIC_MCLAIM(hart);
	return irq;
}

void complete(uint64_t irq)
{
	uint64_t hart = r_mhartid();
	*(uint32_t *)PLIC_MCOMPLETE(hart) = irq;
}

void Init_plic()
{
	printk("Initial plic...\n");
	uint64_t hart = r_tp();
	*(uint32_t *)PLIC_PRIORITY(UART0_IRQ) = 1;
	*(uint32_t *)PLIC_PRIORITY(VIRTIO0_IRQ) = 1;
	
	*(uint32_t *)PLIC_MENABLE(hart) = (1 << UART0_IRQ) | (1 << VIRTIO0_IRQ);
	
	*(uint32_t *)PLIC_MTHRESHOLD(hart) = 0;

	w_mie(r_mie() | MEIE);
	w_mstatus(r_mstatus() | EA);
}
